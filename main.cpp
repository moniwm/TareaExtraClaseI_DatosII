#include <iostream>
#include "LinkedList.h"

int main() {
    LinkedList<std::string> *list = new LinkedList<std::string>();
    list->insertElement("Hola");
    list->insertElement("soy");
    list->insertElement("que tal");
    list->insertElement("Moni");
    list->printList();

    list->remove("soy");

    list->printList();
    return 0;
}

