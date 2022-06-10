#ifndef LIST_ITEM_HPP_
#define LIST_ITEM_HPP_

#include <string>

struct ListItem {
    std::string m_item_name;
    ListItem();
    ListItem(std::string item_name);
    ~ListItem();
};


#endif