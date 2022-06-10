#include <imgui_widgets/list_box.hpp>

void ListBox::add_item(std::string item_name) {
    std::shared_ptr<ListItem> item = std::make_shared<ListItem>(item_name);
    m_items.push_back(item);
}

void ListBox::render() {
   
}