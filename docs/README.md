# VMSS2.0 Documentation

This documentation is organized to provide users with comprehensive guidance on the VMSS2.0 framework, focusing on avac (Aupera Video Analytics Client Web APP), nodes (also known as calculators), packets, and the implementation of custom nodes for supported devices.

## Directory Structure

The documentation is structured into several key areas:

- [`avac/`](./avac/): Contains specific documentation related to usage of our (Web App)[https://vmss.auperatechnologies.com/].
- [`basic_node_creation/`](./basic_node_creation/): A guide to create custom node for your own custom logic. 
- [`nodes`](./nodes/): A comprehensive guide to creating and managing nodes within VMSS2.0.
- [`packet_documentation/`](https://auperatech.github.io/VMSS2.0/packet_documentation/index.html): Includes detailed documentation on packet structure and usage. Access the documentation online at [Packet Documentation](https://auperatech.github.io/VMSS2.0/packet_documentation/index.html).
- [`protos`](./protos/): AVAP-specific documentation.
- [`smart_edge_box/`](./smart_edge_box/): Provides information on implementing nodes for the Smart Edge Box device.

## About VMSS2.0

VMSS2.0 is designed to operate on video and image inputs, defined within a single proto (.pbtxt) file. Each VMSS2.0 pipeline outlines a graph comprising nodes (or calculators), interconnected through packets. This design allows for a modular and flexible approach to building video and image processing pipelines.

### Nodes (Calculators)

Nodes, also known as calculators, are the fundamental building blocks of any VMSS2.0 pipeline. They perform specific operations on packets, processing input data, and producing output for subsequent nodes in the pipeline.

### Packets

Packets are the primary data structure used for data transmission between nodes in a pipeline. They carry the processed data (e.g., video frames, images, metadata) from one node to the next, facilitating the seamless flow of information.

### Custom Node Implementation

For each supported device, custom node implementations can be created. With the exception of AEVA Smart Edgebox device side which is hosted [here](./smart_edge_box/basic_node_creation.md) you can follow the instructions [here](./basic_node_creation/) to create your own custom node. 

## Conclusion

This documentation aims to provide a clear and concise guide to understanding and utilizing the VMSS2.0 framework effectively. For further information or specific inquiries, please refer to the detailed documentation within each directory or file mentioned above.
