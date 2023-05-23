#pragma once

// std headers
// #include <atomic>
// #include <cstddef>
// #include <functional>
// #include <mutex>
// #include <type_traits>

// sdk headers
// #include <boost/make_shared.hpp>
// #include <boost/shared_ptr.hpp>

// local headers
// #include <aup/avaf/error.h>

// #define AUP_AVAF_TYPE_NAME_STR(typename_) #typename_

// namespace aup::avaf {

// template <typename PB>
// class PacketBase;

// template <typename PP>
// class PacketPtr
// {
// public:
// 	typedef std::function<void(PacketPtr<PP>& pp, void* arg_vp)> ref_cnt_dec_to_1_func_t;

// private:
// 	class Shared
// 	{
// 		PP* pp;
// 		uint32_t ref_cnt;
// 		void* arg_vp;
// 		ref_cnt_dec_to_1_func_t ref_change_func;
// 	};
// 	Shared* shared;

// public:
// 	void set_arg_vp(void* arg_vp) const { this->arg_vp = arg_vp; }
// 	void* pv_get_shared_vp() { return (void*)shared; }
// 	void pv_set_shared_vp(void* shared_vp) { shared = (Shared*)shared_vp; }
// 	constexpr PacketPtr() noexcept : shared(NULL)
// 	{
// 		// static_assert(std::is_base_of<PacketBase, PP>(), "PP must have PacketBase as base");
// 	}
// 	constexpr PacketPtr(std::nullptr_t /* unused */) noexcept : shared(NULL) {}
// 	PacketPtr(PP* pp) noexcept
// 	{
// 		if (!pp) {
// 			return;
// 		}
// 		shared          = new Shared;
// 		shared->pp      = pp;
// 		shared->ref_cnt = 1;
// 	}
// 	PacketPtr(PP* pp, void* shared_vp)
// 	{
// 		if (!pp) {
// 			return;
// 		}
// 		shared = (Shared*)shared_vp;
// 		shared->ref_cnt++;
// 	}
// 	template <typename PP2>
// 	PacketPtr(const PacketPtr<PP2>& pp2) noexcept
// 	{
// 		static_assert(std::is_convertible<PP2*, PP*>(), "PP2 must be convertible to PP");
// 		shared = (Shared*)pp2.pv_get_shared_vp();
// 		if (shared) {
// 			shared->ref_cnt++;
// 		}
// 	}
// 	PacketPtr(const PacketPtr& pp) noexcept
// 	{
// 		shared = (Shared*)pp.pv_get_shared_vp();
// 		if (shared) {
// 			shared->ref_cnt++;
// 		}
// 	}
// 	PacketPtr(PacketPtr&& pp) noexcept
// 	{
// 		shared = (Shared*)pp.pv_get_shared_vp();
// 		pp.pv_set_shared_vp(NULL);
// 	}
// 	template <typename PP2>
// 	PacketPtr(PacketPtr<PP2>&& pp2) noexcept
// 	{
// 		static_assert(std::is_convertible<PP2*, PP*>(), "PP2 must be convertible to PP.");
// 		shared = (Shared*)pp2.pv_get_shared_vp();
// 		pp2.pv_set_shared_vp(NULL);
// 	}
// 	~PacketPtr() {}
// 	PacketPtr& operator=(std::nullptr_t /* unused */) noexcept
// 	{
// 		if (!shared) {
// 			return *this;
// 		}
// 		if (--shared->ref_cnt == 1 && shared->ref_change_func) {
// 			shared->ref_change_func(*this, shared->arg_vp);
// 		} else if (shared->ref_cnt == 0) {
// 			delete shared->pp;
// 			delete shared;
// 			shared = NULL;
// 		}
// 		return *this;
// 	}
// 	template <typename PP2>
// 	PacketPtr& operator=(const PacketPtr<PP2>& pp2)
// 	{
// 		static_assert(std::is_convertible<PP2*, PP*>(), "PP2 must be convertible to PP.");
// 		if (pp2->get() == NULL) {
// 			return this->operator=(nullptr);
// 		}
// 		if ((void*)this->get() == (void*)pp2->get()) {
// 			return *this;
// 		}
// 		if (this->get()) {
// 			if (--shared->ref_cnt == 1 && shared->ref_change_func) {
// 				shared->ref_change_func(*this, shared->arg_vp);
// 			} else if (shared->ref_cnt == 0) {
// 				delete shared->pp;
// 				delete shared;
// 			}
// 		}
// 		shared = (Shared*)pp2.pv_get_shared_vp();
// 		shared->ref_cnt++;
// 		return *this;
// 	}
// 	PacketPtr& operator=(PacketPtr&& pp)
// 	{
// 		if (pp->get() == NULL) {
// 			return this->operator=(nullptr);
// 		}
// 		if (this->get() == pp->get()) {
// 			return this;
// 		}
// 		if (this->get()) {
// 			if (--shared->ref_cnt == 1 && shared->ref_change_func) {
// 				shared->ref_change_func(*this, shared->arg_vp);
// 			} else if (shared->ref_cnt == 0) {
// 				delete shared->pp;
// 				delete shared;
// 			}
// 		}
// 		shared = (Shared*)pp.pv_get_shared_vp();
// 		pp.pv_set_shared_vp(NULL);
// 	}
// 	template <typename PP2>
// 	PacketPtr& operator=(PacketPtr<PP2>&& pp2)
// 	{
// 		static_assert(std::is_convertible<PP2*, PP*>(), "PP2 must be convertible to PP.");
// 		if (pp2->get() == NULL) {
// 			return this->operator=(nullptr);
// 		}
// 		if ((void*)this->get() == (void*)pp2->get()) {
// 			return this;
// 		}
// 		if (this->get()) {
// 			if (--shared->ref_cnt == 1 && shared->ref_change_func) {
// 				shared->ref_change_func(*this, shared->arg_vp);
// 			} else if (shared->ref_cnt == 0) {
// 				delete shared->pp;
// 				delete shared;
// 			}
// 		}
// 		shared = (Shared*)pp2.pv_get_shared_vp();
// 		pp2.pv_set_shared_vp(NULL);
// 		return *this;
// 	}
// 	PP* operator->() const noexcept { return shared ? shared->pp : NULL; }
// 	PP operator*()
// 	{
// 		if (!shared) {
// 			throw std::runtime_error("empty pointer");
// 		}
// 		return *shared->pp;
// 	}
// 	uint32_t use_count() const { return shared ? shared->ref_cnt : 0; }
// 	void swap(PacketPtr& other) noexcept
// 	{
// 		Shared* other_shared = (Shared*)other.pv_get_shared_vp();
// 		other.pv_set_shared_vp((void*)(this->shared));
// 		shared = other_shared;
// 	}
// };

// template <typename PP>
// inline bool operator==(PacketPtr<PP> pp, std::nullptr_t /*unused*/)
// {
// 	return pp.get() == NULL;
// }

// template <typename PP>
// inline bool operator==(std::nullptr_t /*unused*/, PacketPtr<PP> pp)
// {
// 	return pp.get() == NULL;
// }

// template <typename PP>
// inline bool operator!=(PacketPtr<PP> pp, std::nullptr_t /*unused*/)
// {
// 	return pp.get() != NULL;
// }

// template <typename PP>
// inline bool operator!=(std::nullptr_t /*unused*/, PacketPtr<PP> pp)
// {
// 	return pp.get() != NULL;
// }

// template <typename PP, typename PP2>
// PacketPtr<PP> static_packet_cast(const PacketPtr<PP2>& pp2)
// {
// 	return PacketPtr<PP>(static_cast<PP*>(pp2.get()), pp2.pv_get_shared_vp());
// }

// template <typename PP, typename PP2>
// PacketPtr<PP> const_packet_cast(const PacketPtr<PP2>& pp2)
// {
// 	return PacketPtr<PP>(const_cast<PP*>(pp2.get()), pp2.pv_get_shared_vp());
// }

// template <typename PP, typename PP2>
// PacketPtr<PP> dynamic_packet_cast(const PacketPtr<PP2>& pp2)
// {
// 	return PacketPtr<PP>(dynamic_cast<PP*>(pp2.get()), pp2.pv_get_shared_vp());
// }

// template <typename PP, typename PP2>
// PacketPtr<PP> reinterpret_packet_cast(const PacketPtr<PP2>& pp2)
// {
// 	return PacketPtr<PP>(reinterpret_cast<PP*>(pp2.get()), pp2.pv_get_shared_vp());
// }

// template <typename PP, typename... Args>
// inline PacketPtr<PP> make_packet(Args&&... args)
// {
// 	// static_assert(std::is_base_of<PacketBase, PP>(), "PP must have PacketBase as base");
// 	PP* pp = new PP(args...);
// 	return PacketPtr<PP>(pp);
// }

// } // namespace aup::avaf

// namespace aup::avaf {

// template <typename T>
// class PacketPtr;

// namespace detail {

// template <typename T, typename Y>
// inline void pp_pointer_construct(aup::avaf::PacketPtr<T>* ppx, Y* p, boost::detail::shared_count& pn)
// {
// 	boost::detail::shared_count(p).swap(pn);
// }

// } // namespace detail

// class PacketBase;

// template <class T>
// class PacketPtr
// {
// private:
// 	// Borland 5.5.1 specific workaround
// 	typedef PacketPtr<T> this_type;

// public:
// 	typedef typename boost::detail::sp_element<T>::type element_type;

// 	constexpr PacketPtr() noexcept : px(0), pn()
// 	{
// 		static_assert(std::is_convertible<T*, const PacketBase* const>(),
// 		              "T must be base class of aup::avaf::PacketBase");
// 	}

// 	constexpr PacketPtr(std::nullptr_t) noexcept : px(0), pn() {}

// 	PacketPtr(boost::detail::sp_internal_constructor_tag, element_type* px_,
// 	          boost::detail::shared_count const& pn_) noexcept
// 	    : px(px_), pn(pn_)
// 	{
// 	}

// 	constexpr PacketPtr(boost::detail::sp_internal_constructor_tag, element_type* px_,
// 	                    boost::detail::shared_count&& pn_) noexcept
// 	    : px(px_), pn(std::move(pn_))
// 	{
// 	}

// 	template <class Y>
// 	explicit PacketPtr(Y* p) : px(p), pn()
// 	{
// 		aup::avaf::detail::pp_pointer_construct(this, p, pn);
// 	}

// 	template <class Y, class D>
// 	PacketPtr(Y* p, D d) : px(p), pn(p, d)
// 	{
// 	}

// 	template <class D>
// 	PacketPtr(boost::detail::sp_nullptr_t p, D d) : px(p), pn(p, d)
// 	{
// 	}

// 	template <class Y, class D, class A>
// 	PacketPtr(Y* p, D d, A a) : px(p), pn(p, d, a)
// 	{
// 	}

// 	template <class D, class A>
// 	PacketPtr(std::nullptr_t p, D d, A a) : px(p), pn(p, d, a)
// 	{
// 	}

// 	PacketPtr(PacketPtr const& r) noexcept : px(r.px), pn(r.pn) {}

// 	template <class Y>
// 	PacketPtr(PacketPtr<Y> const& r,
// 	          typename boost::detail::sp_enable_if_convertible<Y, T>::type = boost::detail::sp_empty()) noexcept
// 	    : px(r.px), pn(r.pn)
// 	{
// 		static_assert(std::is_convertible<Y*, T*>(), "types are not convertible.");
// 	}

// 	// aliasing
// 	template <class Y>
// 	PacketPtr(PacketPtr<Y> const& r, element_type* p) noexcept : px(p), pn(r.pn)
// 	{
// 	}

// 	PacketPtr& operator=(PacketPtr const& r) noexcept
// 	{
// 		this_type(r).swap(*this);
// 		return *this;
// 	}

// 	template <class Y>
// 	PacketPtr& operator=(PacketPtr<Y> const& r) noexcept
// 	{
// 		this_type(r).swap(*this);
// 		return *this;
// 	}

// 	PacketPtr(PacketPtr&& r) noexcept : px(r.px), pn()
// 	{
// 		pn.swap(r.pn);
// 		r.px = 0;
// 	}

// 	template <class Y>
// 	PacketPtr(PacketPtr<Y>&& r,
// 	          typename boost::detail::sp_enable_if_convertible<Y, T>::type = boost::detail::sp_empty()) noexcept
// 	    : px(r.px), pn()
// 	{
// 		boost::detail::sp_assert_convertible<Y, T>();

// 		pn.swap(r.pn);
// 		r.px = 0;
// 	}

// 	PacketPtr& operator=(PacketPtr&& r) noexcept
// 	{
// 		this_type(static_cast<PacketPtr&&>(r)).swap(*this);
// 		return *this;
// 	}

// 	template <class Y>
// 	PacketPtr& operator=(PacketPtr<Y>&& r) noexcept
// 	{
// 		this_type(static_cast<PacketPtr<Y>&&>(r)).swap(*this);
// 		return *this;
// 	}

// 	// aliasing move
// 	template <class Y>
// 	PacketPtr(PacketPtr<Y>&& r, element_type* p) noexcept : px(p), pn()
// 	{
// 		pn.swap(r.pn);
// 		r.px = 0;
// 	}

// 	PacketPtr& operator=(std::nullptr_t) noexcept
// 	{
// 		this_type().swap(*this);
// 		return *this;
// 	}

// 	void reset() noexcept { this_type().swap(*this); }

// 	template <class Y>
// 	void reset(Y* p) // Y must be complete
// 	{
// 		assert(p == 0 || p != px); // catch self-reset errors
// 		this_type(p).swap(*this);
// 	}

// 	template <class Y, class D>
// 	void reset(Y* p, D d)
// 	{
// 		this_type(p, d).swap(*this);
// 	}

// 	template <class Y, class D, class A>
// 	void reset(Y* p, D d, A a)
// 	{
// 		this_type(p, d, a).swap(*this);
// 	}

// 	template <class Y>
// 	void reset(PacketPtr<Y> const& r, element_type* p) noexcept
// 	{
// 		this_type(r, p).swap(*this);
// 	}

// 	template <class Y>
// 	void reset(PacketPtr<Y>&& r, element_type* p) noexcept
// 	{
// 		this_type(static_cast<PacketPtr<Y>&&>(r), p).swap(*this);
// 	}

// 	typename boost::detail::sp_dereference<T>::type operator*() const noexcept
// 	{
// 		assert(px != 0);
// 		return *px;
// 	}

// 	typename boost::detail::sp_member_access<T>::type operator->() const noexcept
// 	{
// 		assert(px != 0);
// 		return px;
// 	}

// 	typename boost::detail::sp_array_access<T>::type operator[](std::ptrdiff_t i) const noexcept
// 	{
// 		assert(px != 0);
// 		assert(i >= 0 && (i < boost::detail::sp_extent<T>::value || boost::detail::sp_extent<T>::value == 0));

// 		return static_cast<typename boost::detail::sp_array_access<T>::type>(px[i]);
// 	}

// 	element_type* get() const noexcept { return px; }

// 	explicit operator bool() const noexcept { return px != 0; }

// 	bool unique() const noexcept { return pn.unique(); }

// 	long use_count() const noexcept { return pn.use_count(); }

// 	void swap(PacketPtr& other) noexcept
// 	{
// 		std::swap(px, other.px);
// 		pn.swap(other.pn);
// 	}

// 	template <class Y>
// 	bool owner_before(PacketPtr<Y> const& rhs) const noexcept
// 	{
// 		return pn < rhs.pn;
// 	}

// 	void* _internal_get_deleter(boost::detail::sp_typeinfo const& ti) const noexcept { return pn.get_deleter(ti); }

// 	void* _internal_get_local_deleter(boost::detail::sp_typeinfo const& ti) const noexcept
// 	{
// 		return pn.get_local_deleter(ti);
// 	}

// 	void* _internal_get_untyped_deleter() const noexcept { return pn.get_untyped_deleter(); }

// 	bool _internal_equiv(PacketPtr const& r) const noexcept { return px == r.px && pn == r.pn; }

// 	boost::detail::shared_count _internal_count() const noexcept { return pn; }

// 	// Tasteless as this may seem, making all members public allows member templates
// 	// to work in the absence of member template friends. (Matthew Langston)

// private:
// 	template <class Y>
// 	friend class PacketPtr;

// 	element_type* px;               // contained pointer
// 	boost::detail::shared_count pn; // reference counter

// }; // PacketPtr

// template <class T, class U>
// inline bool operator==(PacketPtr<T> const& a, PacketPtr<U> const& b) noexcept
// {
// 	return a.get() == b.get();
// }

// template <class T, class U>
// inline bool operator!=(PacketPtr<T> const& a, PacketPtr<U> const& b) noexcept
// {
// 	return a.get() != b.get();
// }

// template <class T>
// inline bool operator==(PacketPtr<T> const& p, std::nullptr_t) noexcept
// {
// 	return p.get() == 0;
// }

// template <class T>
// inline bool operator==(boost::detail::sp_nullptr_t, PacketPtr<T> const& p) noexcept
// {
// 	return p.get() == 0;
// }

// template <class T>
// inline bool operator!=(PacketPtr<T> const& p, boost::detail::sp_nullptr_t) noexcept
// {
// 	return p.get() != 0;
// }

// template <class T>
// inline bool operator!=(boost::detail::sp_nullptr_t, PacketPtr<T> const& p) noexcept
// {
// 	return p.get() != 0;
// }

// template <class T, class U>
// inline bool operator<(PacketPtr<T> const& a, PacketPtr<U> const& b) noexcept
// {
// 	return a.owner_before(b);
// }

// template <class T>
// inline void swap(PacketPtr<T>& a, PacketPtr<T>& b) noexcept
// {
// 	a.swap(b);
// }

// template <class T, class U>
// PacketPtr<T> static_packet_cast(PacketPtr<U> const& r) noexcept
// {
// 	(void)static_cast<T*>(static_cast<U*>(0));

// 	typedef typename PacketPtr<T>::element_type E;

// 	E* p = static_cast<E*>(r.get());
// 	return PacketPtr<T>(r, p);
// }

// template <class T, class U>
// PacketPtr<T> const_packet_cast(PacketPtr<U> const& r) noexcept
// {
// 	(void)const_cast<T*>(static_cast<U*>(0));

// 	typedef typename PacketPtr<T>::element_type E;

// 	E* p = const_cast<E*>(r.get());
// 	return PacketPtr<T>(r, p);
// }

// template <class T, class U>
// PacketPtr<T> dynamic_packet_cast(PacketPtr<U> const& r) noexcept
// {
// 	(void)dynamic_cast<T*>(static_cast<U*>(0));

// 	typedef typename PacketPtr<T>::element_type E;

// 	E* p = dynamic_cast<E*>(r.get());
// 	return p ? PacketPtr<T>(r, p) : PacketPtr<T>();
// }

// template <class T, class U>
// PacketPtr<T> reinterpret_packet_cast(PacketPtr<U> const& r) noexcept
// {
// 	(void)reinterpret_cast<T*>(static_cast<U*>(0));

// 	typedef typename PacketPtr<T>::element_type E;

// 	E* p = reinterpret_cast<E*>(r.get());
// 	return PacketPtr<T>(r, p);
// }

// template <class T, class U>
// PacketPtr<T> static_packet_cast(PacketPtr<U>&& r) noexcept
// {
// 	(void)static_cast<T*>(static_cast<U*>(0));

// 	typedef typename PacketPtr<T>::element_type E;

// 	E* p = static_cast<E*>(r.get());
// 	return PacketPtr<T>(std::move(r), p);
// }

// template <class T, class U>
// PacketPtr<T> const_packet_cast(PacketPtr<U>&& r) noexcept
// {
// 	(void)const_cast<T*>(static_cast<U*>(0));

// 	typedef typename PacketPtr<T>::element_type E;

// 	E* p = const_cast<E*>(r.get());
// 	return PacketPtr<T>(std::move(r), p);
// }

// template <class T, class U>
// PacketPtr<T> dynamic_packet_cast(PacketPtr<U>&& r) noexcept
// {
// 	(void)dynamic_cast<T*>(static_cast<U*>(0));

// 	typedef typename PacketPtr<T>::element_type E;

// 	E* p = dynamic_cast<E*>(r.get());
// 	return p ? PacketPtr<T>(std::move(r), p) : PacketPtr<T>();
// }

// template <class T, class U>
// PacketPtr<T> reinterpret_packet_cast(PacketPtr<U>&& r) noexcept
// {
// 	(void)reinterpret_cast<T*>(static_cast<U*>(0));

// 	typedef typename PacketPtr<T>::element_type E;

// 	E* p = reinterpret_cast<E*>(r.get());
// 	return PacketPtr<T>(std::move(r), p);
// }

// template <typename T, typename... Args>
// inline PacketPtr<T> make_packet(Args&&... args)
// {
// 	PacketPtr<T> pt(static_cast<T*>(0), BOOST_SP_MSD(T));

// 	boost::detail::sp_ms_deleter<T>* pd =
// 	    static_cast<boost::detail::sp_ms_deleter<T>*>(pt._internal_get_untyped_deleter());

// 	void* pv = pd->address();

// 	::new (pv) T(boost::detail::sp_forward<Args>(args)...);
// 	pd->set_initialized();

// 	T* pt2 = static_cast<T*>(pv);

// 	return boost::shared_ptr<T>(pt, pt2);
// }

// } // namespace aup::avaf

// namespace aup::avaf {

// template <typename T>
// class PacketPtr : public boost::shared_ptr<T>
// {
// public:
// 	constexpr PacketPtr() noexcept : boost::shared_ptr<T>()
// 	{
// 		static_assert(std::is_convertible<T*, const PacketBase* const>(),
// 		              "T must be base class of aup::avaf::PacketBase");
// 	}
// 	constexpr PacketPtr(std::nullptr_t np) noexcept : boost::shared_ptr<T>(np) {}
// 	constexpr PacketPtr(boost::detail::sp_internal_constructor_tag, boost::shared_ptr<T>::element_type* px,
// 	                    boost::detail::shared_count const& pn) noexcept
// 	    : boost::shared_ptr<T>(px, pn)
// 	{
// 	}
// 	constexpr PacketPtr(boost::detail::sp_internal_constructor_tag, boost::shared_ptr<T>::element_type* px,
// 	                    boost::detail::shared_count&& pn) noexcept
// 	    : boost::shared_ptr<T>()
// 	{
// 	}
// 	template <typename Y>
// 	explicit PacketPtr(Y* p) : boost::shared_ptr<X>(p)
// 	{
// 	}
// 	template <typename Y, typename D>
// 	PacketPtr(Y* y, D d) : boost::shared_ptr<T>(p, d)
// 	{
// 	}
// 	template <typename D>
// 	PacketPtr(std::nullptr_t p, D d) : boost::shared_ptr<T>(p, d)
// 	{
// 	}
// 	template <typename Y, typename D, typename A>
// 	PacketPtr(Y* p, D d, A a) : boost::shared_ptr<T>(p, d, a)
// 	{
// 	}
// 	template <typename D, typename A>
// 	PacketPtr(std::nullptr_t p, D d, A a) : boost::shared_ptr<T>(p, d, a)
// 	{
// 	}
// 	PacketPtr(boost::shared_ptr const& r) noexcept : boost::shared_ptr<T>(r) {}
// 	template <typename Y>
// 	PacketPtr(boost::shared_ptr<Y>& r,
// 	          typename boost::detail::sp_enable_if_convertible<Y, T>::type = boost::detail::sp_empty()) noexcept
// 	    : boost::shared_ptr<T>(r)
// 	{
// 	}
// };

#include <boost/smart_ptr/make_shared_object.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
namespace aup::avaf {

class PacketBase;

template <typename Tp>
using PacketPtr = boost::shared_ptr<Tp>;

template <typename Tp, typename... Args>
inline PacketPtr<Tp> make_packet(Args&&... args)
{
	static_assert(std::is_convertible<Tp*, const PacketBase* const>(),
	              "Tp must be base class of aup::avaf::PacketBase");
	return boost::make_shared<Tp>(args...);
}

template <typename Tp, typename Up>
inline PacketPtr<Tp> static_packet_cast(const PacketPtr<Up>& ptr) noexcept
{
	static_assert(std::is_convertible<Tp*, const PacketBase* const>(),
	              "Tp must be base class of aup::avaf::PacketBase");
	static_assert(std::is_convertible<Up*, const PacketBase* const>(),
	              "Tp must be base class of aup::avaf::PacketBase");
	return boost::static_pointer_cast<Tp>(ptr);
}

template <typename Tp, typename Up>
inline PacketPtr<Tp> const_packet_cast(const PacketPtr<Up>& ptr) noexcept
{
	static_assert(std::is_convertible<Tp*, const PacketBase* const>(),
	              "Tp must be base class of aup::avaf::PacketBase");
	static_assert(std::is_convertible<Up*, const PacketBase* const>(),
	              "Tp must be base class of aup::avaf::PacketBase");
	return boost::const_pointer_cast<Tp>(ptr);
}

template <typename Tp, typename Up>
inline PacketPtr<Tp> dynamic_packet_cast(const PacketPtr<Up>& ptr) noexcept
{
	static_assert(std::is_convertible<Tp*, const PacketBase* const>(),
	              "Tp must be base class of aup::avaf::PacketBase");
	static_assert(std::is_convertible<Up*, const PacketBase* const>(),
	              "Tp must be base class of aup::avaf::PacketBase");
	return boost::dynamic_pointer_cast<Tp>(ptr);
}

template <typename Tp, typename Up>
inline PacketPtr<Tp> reinterpret_packet_cast(const PacketPtr<Up>& ptr) noexcept
{
	static_assert(std::is_convertible<Tp*, const PacketBase* const>(),
	              "Tp must be base class of aup::avaf::PacketBase");
	static_assert(std::is_convertible<Up*, const PacketBase* const>(),
	              "Tp must be base class of aup::avaf::PacketBase");
	return boost::reinterpret_pointer_cast<Tp>(ptr);
}

} // namespace aup::avaf