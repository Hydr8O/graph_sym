#ifndef LIST_BOX_HPP_
#define LIST_BOX_HPP_

#include <imgui.h>
#include <memory>
#include <vector>
#include <string>

#include <imgui_widgets/list_item.hpp>

typedef std::vector<std::shared_ptr<ListItem>> ListItems;
class ListBox {
private:
    ListItems m_items;

public:
    void add_item(std::string item_name);
    void render();
};


#endif