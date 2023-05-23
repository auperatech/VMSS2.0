#pragma once

// std headers
#include <type_traits>

// local headers
#include "aup/avaf/contract.h"
#include "aup/avaf/node.h"

#define AUP_AVAF_CALC_APIS_MAX_TYPE_MASK_SZ 16
#define AUP_AVAF_CALC_APIS_STR_SZ 256

namespace aup::avaf {

typedef int32_t (*CALCULATOR_ENTRY)(void);
typedef struct CalculatorAPIs CalculatorAPIs;

enum
{
	HARDWARE_TYPE_NONE         = 0,
	HARDWARE_TYPE_X86_64       = 0x1,
	HARDWARE_TYPE_X86          = 0x2,
	HARDWARE_TYPE_ARM64        = 0x4,
	HARDWARE_TYPE_XLNX_V205    = 0x100,
	HARDWARE_TYPE_XLNX_U30     = 0x200,
	HARDWARE_TYPE_XLNX_U50     = 0x400,
	HARDWARE_TYPE_XLNX_V70     = 0x800,
	HARDWARE_TYPE_XLNX_VCK5000 = 0x1000,
	HARDWARE_TYPE_XLNX_ALL     = HARDWARE_TYPE_XLNX_V205 | HARDWARE_TYPE_XLNX_U30 | HARDWARE_TYPE_XLNX_U50 |
	                         HARDWARE_TYPE_XLNX_V70 | HARDWARE_TYPE_XLNX_VCK5000,
	HARDWARE_TYPE_AMD_EPYC = 0x1'0000,
	HARDWARE_TYPE_MAX      = 0x8000'0000'0000'0000
};

struct CalculatorAPIs
{
	char vendor[AUP_AVAF_CALC_APIS_STR_SZ]; // calculator vendor
	char name[AUP_AVAF_CALC_APIS_STR_SZ];   // calculator name
	char desc[AUP_AVAF_CALC_APIS_STR_SZ];   // some detail description for plugin
	bool has_execute;
	uint64_t hw_type_masks[AUP_AVAF_CALC_APIS_MAX_TYPE_MASK_SZ]; // each element masks the HARDWARE_TYPE_XXX
	// entry to open the calculator, load its options, generate its contract and return the calculator pointer
	ErrorCode (*open)(const Node*, void**);
	// entry point to get the contract of the calculator
	/*
	 * Contracts get the node options. Contract might reject the node options in which case it will be NULL;
	 * get input type sample as an array of PacketBase. Framework will use this information to validate the first time
	 * dequeue or peek has happened */
	ErrorCode (*get_contract)(void*, std::shared_ptr<Contract>&);
	ErrorCode (*initialize)(void*, std::string&);
	/* entry to process the data come from multiple input streams,
	 * if define to NULL, then user need to call aup::avaf::Node::dequeue to get data from input streams in separate
	 * thread
	 */
	ErrorCode (*execute)(void*);
	// entry to close the calculator
	void (*close)(void*);
};

extern "C"
{
	// common entry  to register the calculator
	int32_t aup_avaf_calculator_register(CalculatorAPIs* calc_apis);
}

// getting calculator apis pointer based on given name and vendor
CalculatorAPIs* get_calculator_apis(std::string vendor, std::string name);

// calculate template that gets a protocol buffer msg as its configuration
template <typename OptionsType>
class CalculatorBase
{
protected:
	std::unique_ptr<OptionsType> options;
	const Node* node;
	virtual ErrorCode fill_contract(std::shared_ptr<Contract>& contract) { return ErrorCode::OK; }

public:
	CalculatorBase(const Node* node) : node(node){};
	virtual ~CalculatorBase() {}
	// inhertior must implement this function
	ErrorCode get_contract(std::shared_ptr<Contract>& contract)
	{
		contract = std::make_shared<Contract>(node->config);
		auto ret = fill_contract(contract);
		if (ret != ErrorCode::OK) {
			return ret;
		}
		// when overriding get_contract, take this function as the template of what to do
		return contract->override_via_config();
	}
	ErrorCode initialize_options()
	{
		options = std::make_unique<OptionsType>();
		for (const ::google::protobuf::Any& object : node->options) {
			if (!object.Is<OptionsType>()) {
				BOOST_LOG_SEV(node->logger()->mlogger(), LOG_ERROR)
				    << "\033[33m" << __FUNCTION__ << "Options do not match with calculator "
				    << node->get_calculator_name() << ":" << node->get_node_name() << "\033[0m" << std::endl;
				return ErrorCode::DATATYPE_MISMATCH;
			}
			if (!object.UnpackTo(options.get())) {
				BOOST_LOG_SEV(node->logger()->mlogger(), LOG_ERROR)
				    << "\033[33m" << __FUNCTION__ << "Error extracting options of calculator "
				    << node->get_calculator_name() << ":" << node->get_node_name() << "\033[0m" << std::endl;
				return ErrorCode::PROTOBUF;
			}
		}
		return ErrorCode::OK;
	}
	// must be implemented by the calculator to initiazilie
	virtual ErrorCode initialize(std::string& err_str) = 0;
	// execute function and whether it is used or not
	bool has_execute;
	virtual ErrorCode execute() { return ErrorCode::OK; };
};

} // namespace aup::avaf

#define AUP_AVAF_HW_TYPE_MASKS_WRAPPER(...) __VA_ARGS__

#define AUP_AVAF_ASSERT_STRING_LITERAL(string_literal_, err_msg_)                                                      \
	static_assert((::std::is_convertible<decltype(string_literal_), const char*>::value &&                             \
	               !::std::is_rvalue_reference<decltype(string_literal_)>::value &&                                    \
	               !::std::is_pointer<decltype(string_literal_)>::value &&                                             \
	               !::std::is_array<decltype(string_literal_)>::value &&                                               \
	               !::std::is_class<decltype(string_literal_)>::value),                                                \
	              err_msg_)

// vendor_: vendor of the calculator
// name_: calculator name in snake_case
// class_: calculator class which is inherited from aup::avaf::CalculatorBase
// options_: protocol buffer option typename
// has_execute_: determines if the calculator has execute callback or not
// description_  : description of the calculator
// hw_type_masks_ : an array of masks each of which indicate a mandatory set of hardwares that are compatible
#define AUP_AVAF_REGISTER_CALCULATOR_EXT(vendor_, name_, class_, options_, has_execute_, description_,                 \
                                         hw_type_masks_...)                                                            \
                                                                                                                       \
	static ::aup::avaf::ErrorCode aup_avaf_calculator_open(const ::aup::avaf::Node* node, void** calc_vp2)             \
	{                                                                                                                  \
		::aup::avaf::CalculatorBase<options_>* calc = new class_(node);                                                \
		*calc_vp2                                   = NULL;                                                            \
		if (!calc) {                                                                                                   \
			return ::aup::avaf::ErrorCode::NO_MEMORY;                                                                  \
		}                                                                                                              \
		::aup::avaf::ErrorCode ec;                                                                                     \
		if ((ec = calc->initialize_options()) != ::aup::avaf::ErrorCode::OK) {                                         \
			delete calc;                                                                                               \
			return ec;                                                                                                 \
		}                                                                                                              \
		*calc_vp2         = (void*)calc;                                                                               \
		calc->has_execute = has_execute_;                                                                              \
		return ::aup::avaf::ErrorCode::OK;                                                                             \
	}                                                                                                                  \
                                                                                                                       \
	static ::aup::avaf::ErrorCode aup_avaf_calculator_get_contract(void* calc_vp,                                      \
	                                                               ::std::shared_ptr<Contract>& contract)              \
	{                                                                                                                  \
		auto calc = (class_*)(calc_vp);                                                                                \
		return calc->get_contract(contract);                                                                           \
	}                                                                                                                  \
                                                                                                                       \
	static ::aup::avaf::ErrorCode aup_avaf_calculator_initialize(void* calc_vp, ::std::string& err_str)                \
	{                                                                                                                  \
		auto calc = (class_*)calc_vp;                                                                                  \
		::aup::avaf::ErrorCode ec;                                                                                     \
		if ((ec = calc->initialize(err_str)) != ::aup::avaf::ErrorCode::OK) {                                          \
			return ec;                                                                                                 \
		}                                                                                                              \
		return ::aup::avaf::ErrorCode::OK;                                                                             \
	}                                                                                                                  \
                                                                                                                       \
	static void aup_avaf_calculator_close(void* calc_vp)                                                               \
	{                                                                                                                  \
		auto calc = (class_*)calc_vp;                                                                                  \
		delete calc;                                                                                                   \
	}                                                                                                                  \
                                                                                                                       \
	static ::aup::avaf::ErrorCode aup_avaf_calculator_execute(void* calc_vp)                                           \
	{                                                                                                                  \
		auto calc = (class_*)calc_vp;                                                                                  \
		if (calc->has_execute) {                                                                                       \
			return calc->execute();                                                                                    \
		}                                                                                                              \
		return ::aup::avaf::ErrorCode::OK;                                                                             \
	}                                                                                                                  \
                                                                                                                       \
	extern "C"                                                                                                         \
	{                                                                                                                  \
		int32_t aup_avaf_calculator_init(void)                                                                         \
		{                                                                                                              \
			AUP_AVAF_ASSERT_STRING_LITERAL(vendor_, "vendor is not string literal");                                   \
			static_assert(sizeof(vendor_) <= AUP_AVAF_CALC_APIS_STR_SZ, "vendor too long");                            \
			AUP_AVAF_ASSERT_STRING_LITERAL(name_, "name is not string literal");                                       \
			static_assert(sizeof(name_) <= AUP_AVAF_CALC_APIS_STR_SZ, "name too long");                                \
			AUP_AVAF_ASSERT_STRING_LITERAL(description_, "description is not string literal");                         \
			static_assert(sizeof(description_) <= AUP_AVAF_CALC_APIS_STR_SZ, "description too long");                  \
			static_assert(::std::is_same<bool, decltype(has_execute_)>(), "has_execute must be a boolean literal");    \
			uint64_t hw_type_masks[] = hw_type_masks_;                                                                 \
			static_assert(sizeof(hw_type_masks) / sizeof(hw_type_masks[0]) <= AUP_AVAF_CALC_APIS_MAX_TYPE_MASK_SZ,     \
			              "too many entries for hardware type");                                                       \
			::aup::avaf::CalculatorAPIs calculator_apis = {                                                            \
			    .has_execute  = has_execute_,                                                                          \
			    .open         = aup_avaf_calculator_open,                                                              \
			    .get_contract = aup_avaf_calculator_get_contract,                                                      \
			    .initialize   = aup_avaf_calculator_initialize,                                                        \
			    .execute      = aup_avaf_calculator_execute,                                                           \
			    .close        = aup_avaf_calculator_close,                                                             \
			};                                                                                                         \
			strcpy(calculator_apis.vendor, vendor_);                                                                   \
			strcpy(calculator_apis.name, name_);                                                                       \
			strcpy(calculator_apis.desc, description_);                                                                \
			for (int i = 0; i < (int)(sizeof(hw_type_masks) / sizeof(hw_type_masks[0])); i++) {                        \
				calculator_apis.hw_type_masks[i] = hw_type_masks[i];                                                   \
			}                                                                                                          \
			return aup_avaf_calculator_register(&calculator_apis);                                                     \
		}                                                                                                              \
	}

#define AUP_AVAF_REGISTER_CALCULATOR(vendor_, name_, class_, options_, description_, hw_type_masks_...)                \
	AUP_AVAF_REGISTER_CALCULATOR_EXT(vendor_, name_, class_, options_, true, description_, hw_type_masks_)

#define AUP_AVAF_REGISTER_CALCULATOR_NO_EXEC(vendor_, name_, class_, options_, description_, hw_type_masks_...)        \
	AUP_AVAF_REGISTER_CALCULATOR_EXT(vendor_, name_, class_, options_, false, description_, hw_type_masks_)

// ...
