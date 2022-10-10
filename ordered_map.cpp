#include <iostream> 
#include <string> 
#include <boost/any.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/member.hpp>
using namespace boost::multi_index; 
using namespace std; 


template<typename K, typename V> 
struct ordered_map{
  struct pair{ 
    K key; 
    V value;
    pair(K key, V value): key(key), value(value){};  
  }; 
  
  typedef multi_index_container<
      pair,        // The type of the elements stored
      indexed_by<    // The indices that our container will support
        sequenced<>,
        ordered_unique<member<pair, K, &pair::key>>
    >
  > ordered_map_container; 

  ordered_map_container map;
  enum {Seq, Ord}; 
    typedef typename ordered_map_container::template nth_index<Seq>::type map_seq_index;
    typedef typename ordered_map_container::template nth_index<Ord>::type map_ord_index;  


  class proxy{ 
    ordered_map<K, V>& p_map; 
    K key; 

    public: 
      proxy(ordered_map<K, V>& p_map, K key): p_map(p_map), key(key){}; 
    
      operator V const &(){ 
        /* get value */ 
        map_ord_index& ord_index = p_map.map.template get<Ord>();

        return ord_index.find(key)->value; 

      }


      proxy& operator=(V const& value){ 
        /* set value */ 
        std::cout << key << std::endl; 
        p_map.map.push_back(pair(key, value)); 
        return *this; 
      }

  }; 

  proxy operator[](K key){
    return proxy(*this, key); 
  }

  typename map_seq_index::iterator begin() const&{ //start iterator
    map_seq_index const& seq_index = map.template get<Seq>(); 
    return seq_index.begin(); 
  }

  typename map_seq_index::iterator end() const&{ //end iterator 
    map_seq_index const& seq_index = map.template get<Seq>();
    return seq_index.end(); 
  }

}; 

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