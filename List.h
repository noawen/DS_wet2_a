//
// Created by Dell on 06/06/2018.
//

#ifndef DS_WET2_A_LIST_H
#define DS_WET2_A_LIST_H

//
// Created by Barr on 24/06/2017.
//


#include <iostream>
#include <string>


using std::string;



//namespace ListExceptions {
class ElementNotFound {};

//}



//using namespace ListExceptions;

namespace List_t {

    template<class T>
    class Node {
        T data;
        Node *previous;
        Node *next;
    public:
        Node() {
            this->data = T();
            this->next = NULL;
            this->previous = NULL;
        }

        Node(const Node &node) {
            this->data = node.data;
            this->next = node.next;
            this->previous = node.previous;
        }

        Node(const T &data) {
            this->data = data;
            this->next = NULL;
            this->previous = NULL;
        }

        //   ~Node() = default;

        Node &operator=(const Node &node) {
            this->data = node.data;
            this->previous = node.previous;
            this->next = node.next;
            return *this;
        }

        bool operator==(const Node &node1) const {
            return (data == node1.data && next == node1.next && previous == node1.previous);
        }

        bool operator!=(const Node &node1) const {
            return !(data == node1.data && next == node1.next && previous == node1.previous);
        }

        T &getData() {
            return this->data;
        }

        Node *getNext() const {
            if(this)
                return this->next;
            return NULL;
        }

        Node *getPrevious() const {
            if(this)
                return this->previous;
            return NULL;
        }

        void setPrevious(Node *node) {
            this->previous = node;
        }

        void setNext(Node *node) {
            this->next = node;
        }

        void swap(Node *node) {
            T temp;
            temp = this->data;
            this->data = node->data;
            node->data = temp;
        }
    };



    template<class T>
    class List {
        Node<T> *head;
        Node<T> *last;
    public:

        class Iterator {
            Node<T> *node;
        public:
            Iterator() {
                this->node = NULL;
            }

            Iterator(Node<T> *node) {
                this->node = node;
            }

            // Iterator(const Iterator &iterator) = default;

            bool operator==(const Iterator &iterator) const {
                return (this->node == iterator.node) ||
                       (this->node->getNext() == NULL && iterator.node->getNext() == NULL);
            }

            bool operator!=(const Iterator &iterator) const {
                return !(this->operator==(iterator));
            }

            //     Iterator &operator=(const Iterator &iterator) = default;

            T& operator*() const {
                if (this->getNode()->getNext() == NULL)
                    throw ElementNotFound();
                return this->node->getData();
            }

            Node<T> *getNode() const {
                return this->node;
            }

            Iterator &operator++() {
                if (this->node->getNext() != NULL)
                    this->node = this->node->getNext();
                return *this;
            }

            Iterator operator++(int) {
                Iterator iterator(*this);
                if (this->node->getNext() != NULL)
                    this->node = this->node->getNext();
                return iterator;
            }

            Iterator &operator--() {
                if (this->node->getPrevious() != NULL)
                    this->node = this->node->getPrevious();
                return *this;
            }

            Iterator operator--(int) {
                Iterator iterator(*this);
                if (this->node->getPrevious() != NULL)
                    this->node = this->node->getPrevious();
                return iterator;
            }
        };

        List() {
            this->head = new Node<T>;
            this->last = new Node<T>;
            head->setNext((this->last));
            last->setPrevious((this->head));
        }

        void insert(const T &data) {
            insert(data, this->end());
        }

        void insert(const T &data, Iterator iterator) {
            int flag_iterator_belong_to_list = 0;
            if (iterator == (this->end()) &&
                (iterator.getNode()->getPrevious() == this->end().getNode()->getPrevious())) {
                Node<T> *new_node = new Node<T>(data);
                this->last->getPrevious()->setNext(new_node);
                new_node->setPrevious(this->last->getPrevious());
                this->last->setPrevious(new_node);
                new_node->setNext(this->last);
                return;
            }

            for (Iterator i = this->begin(); i != this->end(); i++) {
                if (i == iterator) {
                    Node<T> *new_node = new Node<T>(data);
                    new_node->setPrevious(i.getNode()->getPrevious());
                    new_node->setNext(i.getNode());
                    i.getNode()->getPrevious()->setNext((new_node));
                    i.getNode()->setPrevious((new_node));
                    flag_iterator_belong_to_list = 1;
                }
            }

            if (flag_iterator_belong_to_list == 0) {
                // throw ListExceptions::ElementNotFound();
                throw ElementNotFound();
            }
        }

        void remove(Iterator iterator) {
            int flag_iterator_belongs_to_list = 0;
            if (iterator == this->end()) {
                //throw ListExceptions::ElementNotFound();
                throw ElementNotFound();
                return;
            }
            for (Iterator i = this->begin(); i != this->end(); i++) {
                if (i == iterator) {
                    flag_iterator_belongs_to_list = 1;
                    iterator.getNode()->getPrevious()->setNext(i.getNode()->getNext());
                    iterator.getNode()->getNext()->setPrevious(i.getNode()->getPrevious());
                    delete (iterator.getNode());
                    break;
                }
            }
            if (flag_iterator_belongs_to_list == 0)
                // throw ListExceptions::ElementNotFound();
                throw ElementNotFound();
        }

        Iterator begin() const {

            Iterator iterator;
            iterator = (this->head);
            iterator++;
            return iterator;
        }

        Iterator end() const {
            Iterator iterator((this->last));
            return iterator;
        }

        int getSize() const {
            int count = 0;
            for (Iterator i = this->begin(); i != this->end(); i++) {
                count++;
            }
            return count;
        }

        template<class Predicate>
        Iterator find(const Predicate &predicate) {
            Iterator i;
            for (i = this->begin(); i != this->end(); i++) {
                if (predicate(i.operator*())) {
                    return i;
                }
            }
            return i;
        }

        template<class Compare>
        void sort(const Compare &compare) {
            bool swaped = false;
            Iterator end_of_list = this->end();
            end_of_list--;
            for (Iterator i = this->begin(); i != end_of_list; i++) {
                swaped = false;
                for (Iterator j = this->begin(); j != end_of_list; j++) {
                    if (!(compare(j.getNode()->getData(), j.getNode()->getNext()->getData()))) {
                        j.getNode()->swap(j.getNode()->getNext());
                        swaped = true;
                    }
                }
                if (!swaped) {
                    break;
                }
            }
        }

        bool operator==(const List &list) const {
            Iterator i = this->begin();
            Iterator j = list.begin();
            while ((i != this->end() && (j != list.end()) && (i.operator*() == j.operator*()))) {
                i++;
                j++;
            }
            if ((i == this->end()) && (j == list.end())) {
                return true;
            }
            return false;
        }

        bool operator!=(const List &list) const {
            return !(this->operator==(list));
        }

        ~List() {
            for (Iterator i = this->begin(); i != this->end(); i++) {
                this->remove(i);
                i = this->begin();
                i--;
            }
            delete this->head;
            delete this->last;
        }
/*
        void operator=(const List& list){
            for (Iterator it = this->begin(); it != this->end(); ){
                this->remove(it);
                it = this->begin();
            }
            int size = list.getSize();
            Iterator it = list.begin();
            for (int i = 0; i < size; i++){
                this->insert(it.operator*());
                it++;
            }
        }
*/

         List<T>& operator=(const List& list) {
            if (this == &list) {
                return *this;
            }
            Iterator it = begin();
            while (it != end()) {
                Iterator to_delete = it++;
                remove(to_delete);
            }

            for (it = list.begin(); it != list.end(); it++) {
                this->insert(it.operator*());
            }
            return *this;
        }



        List(const List &list) {
            this->head = new Node<T>();
            this->last = new Node<T>();
            //int size = list.getSize();
            this->head->setNext(this->last);
            this->last->setPrevious(this->head);

            for (Iterator i = list.begin(); i != list.end(); i++) {
                this->insert(i.getNode()->getData());
            }
        }

    };
}
#endif //DS_WET2_A_LIST_H
