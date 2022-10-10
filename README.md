# ordered_map
 A map style implementaton that preserves input ordering using boost

### Example Usage 
```cpp
int main(int argc, char** argv){ 

  ordered_map<std::string, boost::any> map; 

  map["string"] = 10; 

  auto value = map["string"]; 

  std::cout << boost::any_cast<int>(value) << std::endl; 

  for(auto it = map.begin(); it != map.end(); ++it){ 
    cout << it -> key << ": " << boost::any_cast<int>(it -> value) << endl; 
  }

  return 0; 
}
```