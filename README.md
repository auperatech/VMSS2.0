- [What is VMSS 2.0?](#what-is-vmss-20)
  - [How to access VMSS 2.0?](#how-to-access-vmss-20)
- [How to evaluate VMSS 2.0?](#how-to-evaluate-vmss-20)
  - [Web Client Examples](#web-client-examples)
  - [Command Line Examples](#command-line-examples)
    - [Predefined Graphs](#predefined-graphs)
    - [Custom Buildable Applications](#custom-buildable-applications)
  - [Steps for creating VMSS2.0 nodes](#steps-for-creating-vmss20-nodes)
  - [Node Initialization](#node-initialization)
  - [Defining the execute method](#defining-the-execute-method)

# What is VMSS 2.0?

VMSS is a software application that functions as a video machine-learning streaming server. Its primary purpose is to provide video analytic services to multiple video streams while efficiently utilizing multiple FPGA resources on a server system.

The latest version, VMSS 2.0, offers several features to create flexible ML pipelines. Instead of plugins, VMSS 2.0 has graph nodes that can have arbitrary types, back edges, and side packets. This allows for arbitrary (and even cyclical) graphs instead of just linear graphs. The graphical user interface of VMSS 2.0 helps users build, configure, and run ML pipelines easily. Customers can use Aupera's node toolkit or create their nodes with the aid of Aupera's node creation framework.

VMSS 2.0 allows packets to be synchronized across multiple streams, enabling stream-aware processing. Users can try any of the models on Xilinx Model Zoo (currently box detector and classifier models) with just a few mouse clicks. Additionally, VMSS 2.0 provides hardware abstraction to run ML pipelines on different platforms, allowing for quick adoption of new hardware. A web-application serves as the visual GUI for the server.

## How to access VMSS 2.0?

VMSS 2.0 has been tested on the following list of hardware:
* KV260/KR260 (AMD)
* VCK5000 (AMD)
* U50 (AMD)
* V70 (AMD)
* SBC EdgeAI Box X7 (Planet Spark)
* V205 (Aupera)

If you have access to one of devices mentioned above, you may find the appropiate setup guide under [setup](https://github.com/auperatech/VMSS2.0/tree/main/docs)

  
If you don't have a compatible hardware, you can access VMSS 2.0 by signing up for a demo account via our website [VMSS2.0 here](https://vmss.auperatechnologies.com/).

# How to evaluate VMSS 2.0?

This repository provides you with various examples to get you started. We can split the examples into 4 different categories:

- Web Client Examples
- Command Line Examples
    - Predefined Graphs
    - Custom Buildable Applications

The examples are orgazined as shown below:
```
├── commandline_examples
│   ├── u30_v205
│   │   ├── box_detector_car
│   │   │   ├── 1input_1output.pbtxt
│   │   │   ├── input.pbtxt
│   │   │   └── output.pbtxt
│   │   ├── box_detector_classifier_cascade
│   │   │   ├── 1input_1output.pbtxt
│   │   │   ├── input.pbtxt
│   │   │   ├── input-vid.pbtxt
│   │   │   ├── output.pbtxt
│   │   │   └── output-vid.pbtxt
│   │   ├── box_detector_retail
│   │   │   ├── 1input_1output.pbtxt
│   │   │   ├── input.pbtxt
│   │   │   └── output.pbtxt
│   │   └── custom_pipelines
│   │       ├── extern
│   │       └── vehicle_classificaiton
│   └── vck5000
│       ├── custom_pipelines
│       │   ├── extern
│       │   └── vehicle_access_control
│       ├── to_run_on_both_crowd_and_retail_videos
│       │   └── box_detector_parallel
│       ├── to_run_on_crowd_videos
│       │   ├── apl_crowd_flow
│       │   └── box_detector
│       └── to_run_on_retail_videos
│           ├── box_detector_classifier_cascade
│           └── smart_retail
└── web_client_examples
    ├── to_run_on_crowd_videos
    │   ├── apl_crowd_flow
    │   │   ├── input.pbtxt
    │   │   ├── output.pbtxt
    │   │   └── using_rtsp.pbtxt
    │   └── box_detector
    │       ├── input.pbtxt
    │       ├── output.pbtxt
    │       └── using_rtsp_1output.pbtxt
    └── to_run_on_retail_videos
        ├── box_detector
        │   ├── input.pbtxt
        │   ├── output.pbtxt
        │   └── using_rtsp_1output.pbtxt
        └── box_detector_classifier_cascade
            ├── input.pbtxt
            ├── output.pbtxt
            └── using_rtsp_1output.pbtxt
```

## Web Client Examples

This a set of examples of predefined graphs that contain different examples showcasing the capabilities of combining different nodes from the Nodes Toolkit to run by simply inserting the provided pbtxt file in our Web Client application.

For each example we have provided under a suggested video. For instance, you can find examples that are suitable to run on a video containing people. Those examples are provided under the directory called `to_run_crowd_video`.

Note that given our web client has a restriction of having one input and one output to display, we have separated the examples for this section. You can find these examples for supported devices in the structure shown below:

## Command Line Examples

The command line examples consists of two categories of examples:

- Predefined Graphs
- Custom Buildable Applications

### Predefined Graphs

These set of examples are exactly similar to what we have provided for Web Client examples. However, these examples don't have the restriction imposed by the Web Client. In order to run these examples the user needs to launce our AVAF_AVAS Docker container:

```
docker container exec -it aupera_server bash
```

Once you start the container, inside the docker you can run any of the provided examples by running `avaser` as shown below:

```
avaser -i [input.pbtxt] -o [output.pbtxt] -c [config_graph.pbtxt]
```

The input argument `-i` expects a pbtxt file where all the input rtsp streams are listed.
The output argumet `-o` exepcts a pbtxt file where all the output rtsp streams are listed.
The config argumet `-c` expects a pbtxt file where the entire pipeline is defined.


### Custom Buildable Applications

This category of examples are provided to illustrate how to build a custom application by creating your own node.

To add a new node, you need to create a folder under custom_pipelines with the source code and .proto (message definition) files of your node. 
To build your node you run:
```
make clean; make -j6; make install
```
Inside the docker you can find them at /opt/aupera/avas/examples/custom_pipelines

This make file will copy the .proto file from your node folder into extern/protos folder. 
Then, it will build and install avap (which registers your proto with the framework).
Finally, it will build and install your node. 
**For U30 nodes the install command of make file will also ssh your node over to the U30 device.
At this point, you can run your node. 

Note:
The extern folder inside of the custom_pipelines folder contains the following:
1. avaf binary. This must not have versions. So if you just built avaf and created libavaf.so.3.0.0, then you need to rename this to libavaf.so and place it inside the extern folder. 

2. avaser binary. This is just called avaser. So if you just built avaser you need to copy the generated binary in this folder. 

3. calculator related headers. Any headers that are calculator (and not framework) specific are placed here. These include library headers (detector.hpp, multitracker.hpp, etc), and calculator specific packets (detect_track_packet.h, etc). You need to update this folder if you generated new packet types, or updated the header for one of the cv libraries that you expect the customer to require for their own nodes. 

4. aup/avaf folder containers the framework related headers and packets. If the framework level headers or packets types change, you need to copy the updated file into this folder

5. protos folder. This contains all the .proto files that the framework recognizes and requires to build avap. This also includes the avap make file. The content of this folder must be identical to the corresponding protos folder in the framework. If you add a new node to the framework, you place the new .proto file here. 

## Steps for creating VMSS2.0 nodes

To create your own VMSS2.0 node, you need to perform the following 6 steps:

1. Write a `.proto` file (according to protobuf 3 protocol) to specify the options that your node could receive from the `.pbtxt` file specifying a pipeline which includes your node. For example, the following specifies the options for the object (box) visualizer node (included in Auepra’s node toolkit and explained in section 5.3.9):

```proto
syntax = "proto3";

package aup.avaf;

message BoxVisualizerOptions {
    message Color {
        float r = 1;
        float g = 2;
        float b = 3;
    }

    message ClassColor {
        Color color = 1;
        int32 label = 2;
    }

    message Offset {
        float x = 1;
        float y = 2;
    }

    enum InputType {
        INPUT_TYPE_DETECTION = 0;
        INPUT_TYPE_CLASSIFICATION = 1;
    }

    InputType input_type = 1;
    Color text_color = 2;
    Color box_color = 3;
    repeated ClassColor class_color = 4;
    Color default_class_color = 5;
    Offset text_offset = 6;
    int32 box_thickness = 7;
    int32 text_size = 8;
    int32 font = 9;
    double font_scale = 10;
    int32 font_thickness = 11;
    int32 line_type = 12;
}
    
2. Create the class defining the behavior of your node. All VMSS2.0 nodes must extend the `CalculatorBase` class. Note that `CalculatorBase` is a template class and will require the name of the protobuf class specifying the options for your node. In our example, this will be the `BoxVisualizerOptions` class that we created in step 1. In the code snippet below, you can see the header file (`box_visualizer.hpp`) that declares the `BoxVisualizerCalculator` class which specifies the behavior of our box visualizer node.  

    ```c++
    class BoxVisualizerCalculator : public CalculatorBase<BoxVisualizerOptions> 
    { 
        unordered_map<int, Scalar> class_colors; 
        Scalar default_class_color; 
        int init_no; 
        thread viz_thread; 
        void viz_worker(); 
        void handle_detections(); 
        void handle_classifications(); 
  
    protected: 
        void generate_contract() override; 
  
    public: 
        BoxVisualizerCalculator(const ::aup::avaf::Node* node) : CalculatorBase(node) {} 
        ~BoxVisualizerCalculator(); 
        bool initialize() override; 
    };
    ```
    
3. To register your new node in the framework, you need to call one of the two registration macros provided by the framework. The most commonly used macro is AUP_AVAF_REGISTER_CALCULATOR(vendor_, name_, class_, options_, description_, hw_type_masks_...), which has the following parameters:

A. vendor: The name of the vendor of the calculator.

B. name: The name of the calculator, which is usually in snake case.

C. class: The calculator class name.

D. options: The options of the calculator, which are defined via the .proto file.

E. description: An optional description for the calculator, which can be left as an empty string.

F. hw_type_masks: A list of supported hardware types, which can be left empty as {}. If filled, the framework will validate if the calculator is runnable on the current hardware stack or not.

Here's an example of the AUP_AVAF_REGISTER_CALCULATOR macro call to register our box visualizer node:

```c++
AUP_AVAF_REGISTER_CALCULATOR("Aupera", "box_visualizer",
             aup::avaf::BoxVisualizerCalculator,
             aup::avaf::BoxVisualizerOptions,
             "box visualizer calculator",
             {aup::avaf::HARDWARE_TYPE_X86_64,
              aup::avaf::HARDWARE_TYPE_X86}
)
```

If you don't want to use framework features (for advanced users only), you can use the macro AUP_AVAF_REGISTER_CALCULATOR_EXT. This macro gives the ability to not have execute callback. However, using this registry is an advanced topic and is out of the scope of this document.

4. Provide an initialize method for your node. This method will be called right after your node is constructed. To write an initialize method, you need to override the one provided by the `CalculatorBase` class in the declaration of your class. Like below:
```
Aup::avaf::ErrorCode intialize(std::string& err_str) override;
```
You will also need to define the `initialize` method in the definition of your class.

5. Now you will need to provide an execute method for your node. To do this you need to override the `execute()` method provided by the `CalculatorBase` class in the class declaration of your node. Like below: 

```
ErrorCode execute() override;
```

You will also need to define the execute method in the definition of your class.


6. Optionally, you can provide a contract for the inputs to your node. If you do so, then the framework will perform the following configuration and validations: 

- Validate the types of source and sinks of each stream are compatible 
- Enforce if the stream sink types are compatible with each other. 
- Mark other behaviors choices for the stream inputs outputs 
- Select synchronization schemes 

Most of these contract parameters are useful when you intend your node to be used by some other third party. If you decide to register a contract for your node, then in the declaration of the class for your node, you will need to override the `fill_contract()` method as shown in the example above.

Here is an example for `fill_contract()` of license-plate recognizer node: 

```cpp
Aup::avaf::ErrorCode PlateRecognizerCalculator::fill_contract(shared_ptr<Contract>& contract) 
{ 
    if (contract->input_stream_names.size() != 2) { 
        return EC_SIZE_MISMATCH; 
    } 
    if (contract->output_stream_names.size() > 2) { 
        return EC_SIZE_MISMATCH; 
    } 
    vector<aup::detect::Detector::DetectedObject> res; 
    cv::Mat empty; 
    contract->sample_input_packets[0] = make_packet<Detections>(0, 0, 0, res, empty, 0); 
    contract->sample_input_packets[1] = make_packet<ImagePacket>(); 
    if (contract->output_stream_names.size() == 0) { 
        contract->input_attrs_arr[1].set_type(contract->input_attrs_arr[1].SYNCED_MUTABLE); 
    } 
    if (contract->output_stream_names.size() > 0) { 
        contract->sample_output_packets[0] = make_packet<PlateRecognitions>(0); 
    } 
    if (contract->output_stream_names.size() > 1) { 
        contract->sample_output_packets[1] = make_packet<ImagePacket>(); 
    } 
    contract->stream_sync.set_drop_strategy(contract->stream_sync.DROP_INCOMPLETE_PACKETS); 
    return EC_OK; 
}
```

##  Node Initialization

As you saw in above description, the open method of the node will call the initialize method of each node class. The job of the node specific initialization method is to validate the provided input parameters, log them for the user, send or receive any required side packets, and proceed to initializing the member variables that the node requires.  

Most of the nodes in Aupera’s toolkit use libraries contained in our collection of “Hyper Plugin Specific Libraries”. In the example below, you can see the initialization of a rudimentary box detector node. 

```
ErrorCode BoxDetectorCalculator::initialize(string& err_str){ 
    BOOST_LOG_SEV(pNode->logger()->mlogger(), LOG_INFO) << 
    "\033[33m" << __func__ << " box detector options:" << 
    "\033[0m" << endl; 
  
    BOOST_LOG_SEV(pNode->logger()->mlogger(), LOG_INFO) << 
    "\033[33m" << __func__ << " detector type = " << 
    options->detector_type() << "\033[0m" << endl; 
     
    BOOST_LOG_SEV(pNode->logger()->mlogger(), LOG_INFO) << 
    "\033[33m" << __func__ << " kernel name = " << 
    options->kernel_name() << "\033[0m" << endl; 
  
  
    aup::detect::Detector::InitParams init_params = {}; 
    init_params.detector_type = options->detector_type(); 
    init_params.kernel_name = options->kernel_name(); 
    detector = aup::detect::Detector::create(init_params); 
  
    //send the detect_interval as a side message to next node 
    node->enqueue(side_packet_index, 
                 make_packet<DetectIntervalPacket>(detect_interval)); 
  
    return EC_OK; 
}
```

As you can see above, this method will parse the options passed to the node and logs them for the user (this is something all nodes should do as a styling standard). Next, it initializes Aupera’s detector library. Finally, it base64 encodes the detect_interval parameter (that it has received from the user) and queues it as a side packet for downstream nodes.



## Defining the execute method  

***NOTE:*** if you decide to use an execute method you will need to 

execute 

ErrorCode execute() override; 

Impelmented the execute method for your class as described below. 

Use the IMPL_CALCULATOR_WITH_EXECUTE macro to register your node.  

 

The job of the execute method is to receive the inputs from the framework, perform the requested operations, and return the requested outputs. In most cases, the structure of execute methods look very similar to the example below.   
```
ErrorCode AplCrowdFlowCalculator::execute() 
{ 
  // check the status of the graph (i.e pipeline) 
  if (node->get_graph_status() != GRAPH_STATUS_RUNNING) { 
    BOOST_LOG_SEV(node->logger()->mlogger(), LOG_INFO) 
    << __func__ << " called with graph status of: " 
    << node->get_graph_status() << endl; 
  
    return EC_ERROR; 
  } 
  
  auto& streamsData = node->get_stream_data(); 
  
  //read the 1st input stream (error if it doesn't exist) 
  auto data_from_1s_stream =  
    dynamic_packet_cast<Tracks>(streamsData.at(0)); 
  
  //read the 2nd input stream (which may or may not exist) 
  if (streamsData.size() > 1) { 
    auto images = dynamic_packet_cast<Images>(streamsData.at(1)); 
    cv::Mat cvFrame = images->getMat();  
  } 
  
  //do some work to produce some “result” 
  
  //if there are output streams attached 
  //send some results to the 1st output stream 
  if (node->outputStreamsName.size() > 0) { 
    auto errorCode = node->enqueue(0, result); 
    if (errorCode) { 
      BOOST_LOG_SEV(node->logger()->mlogger(), LOG_ERROR) 
      << " vframe enqueue to: " << 
      node->outputStreamsName.at(0).c_str() 
      << " failed. ErrorCode: " << errorCode << endl; 
  
      return EC_ERROR; 
    } 
  } 
  
  return EC_OK; 
} 
```
 

In the example above, we first make sure that the graph is in running status.  

Then we read the 1st input (from the first input stream). In this example, we are assuming that the first input stream is mandatory (i.e., the node doesn’t first check whether there is an input steam), so an error is thrown if this node has no input streams. 

Then, we check if there is a second input stream. If so, then we will read the 1st packet available on this stream. The node assumes that this packet is of type “Images” containing a frame. The next line retrieves the data contained in the images object into cv::Mat format to perform some operation.   

Finally, we check whether there is an output stream available to this node. If so, we enqueue our result object for the 1st output stream of this node.  

***NOTE:*** The results in this example can be any class that extends the `PacketBase class`. Since any such class can be transmitted across different nodes. 



