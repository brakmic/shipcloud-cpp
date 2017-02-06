## ShipCloud Bindings for C++

This repo contains a Visual C++ Solution with two projects:

* ShipCloud [DLL](https://github.com/brakmic/shipcloud-cpp/tree/master/ShipCloud/ShipCloud)
* Console-based [Client](https://github.com/brakmic/shipcloud-cpp/tree/master/ShipCloud/Client)

The DLL provides mechanisms to communicate with the RESTful web services provided by [ShipCloud](https://developers.shipcloud.io/).

However, please, consider this code as **pre-alpha**. For a similar and more complete (JavaScript) version check out [this project](https://github.com/brakmic/shipcloud-js).

### Libraries

This code utilizes some nice C++14 features and relies upon these great libraries: 

* [C++ REST SDK](https://github.com/Microsoft/cpprestsdk) a.k.a. **Casablanca**
* [JSON for Modern C++](https://github.com/nlohmann/json)

### Building

Before building the projects check if you have Nuget-Packages for C++ REST SDK installed on your machine. The JSON header file is located under **vendors** directory.

### Demo 

<img src="https://i.imgsafe.org/84c1f655a8.png" width="850" height="450">

### Configuration

Put your API-key into [config.json](https://github.com/brakmic/shipcloud-cpp/blob/master/ShipCloud/Client/config.json) and start the **client.exe**.

### License 

[MIT](https://github.com/brakmic/shipcloud-cpp/blob/master/LICENSE)