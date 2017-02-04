## ShipCloud C++ Binding

This repo contains a Visual C++ Solution with two projects:

* ShipCloud DLL
* Console-based Client

However, please, consider this code as **pre-alpha**. For a similar and more complete (JavaScript) version check out this [this project](https://github.com/brakmic/shipcloud-js).
The code in this solution utilizes some nice C++14 features and relies upon these great libraries: 

* [C++ REST SDK](https://github.com/Microsoft/cpprestsdk) a.k.a. **Casablanca**
* [JSON for Modern C++](https://github.com/nlohmann/json)

Before building the projects check if you have Nuget-Packages for C++ REST SDK installed on your machine. The JSON header file is located under **vendors** directory.

### License 

[MIT](https://github.com/brakmic/shipcloud-cpp/blob/master/LICENSE)