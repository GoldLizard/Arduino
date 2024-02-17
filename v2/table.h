#ifndef TABLE
#define TABLE


using namespace std;

struct table{ //all because Arduino uses map for a class, so I cant just map<char, uint8_t>
    vector<pair<char, uint8_t>> map = {make_pair('0', 0x3F), make_pair('1', 0x06), make_pair('2', 0x5B), make_pair('3',0x4F), make_pair('4', 0x66),
                                       make_pair('5', 0x6D), make_pair('6', 0x7D), make_pair('7', 0x07), make_pair('8', 0x7F), make_pair('9', 0x6F),
                                       make_pair('-', 0x40),
                                       make_pair('A', 0x77), make_pair('a', 0x5F), make_pair('b', 0x7C), make_pair('C', 0x39), make_pair('c', 0x58), 
                                       make_pair('d', 0x5E), make_pair('E', 0x79), make_pair('F', 0x71), make_pair('G', 0x3D), make_pair('H', 0x76), 
                                       make_pair('h', 0x74), make_pair('I', 0x30), make_pair('J', 0x1E), make_pair('L', 0x38), make_pair('n', 0x54), 
                                       make_pair('O', 0x3F), make_pair('o', 0x5C), make_pair('P', 0x73), make_pair('q', 0x67), make_pair('r', 0x50), 
                                       make_pair('S', 0x6D), make_pair('t', 0x78), make_pair('U', 0x3E), make_pair('u', 0x1C), make_pair('v', 0x1C),
                                       make_pair('y', 0x6E)}; //Solid 8. for undefined characters

    uint8_t GetHex(char param){ //tableName.GetHex('2'); will loop through vector<pair<>>
      for(pair<char, uint8_t> eachPair : map){
        if(eachPair.first == param){ //once it finds make_pair('2', 0x5B), it returns 0x5B
          return eachPair.second;
        }
      }
      return 0xFF; //if character doesnt exist in lookup table, return 8 as an error
    }
};

#endif