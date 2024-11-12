/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

#include <iostream>
using namespace std;

class Solution {
public:
//NOTA: se usa merge sort
    ListNode* sortList(ListNode* head) {
        // Si la lista está vacía o tiene un solo elemento, ya está ordenada y, por ende, se devuelve tal y como está
        if (!head || !head->next) {
            return head;
        }
        // Encuentra el punto medio de la lista para dividirla en dos mitades
        //Fast: Avanza dos nodos a la vez
        //Slow: Avanza un nodo a la vez
        //Por ende, cuando fast llega al final, slow va a la mitad de la lista.
        //Prev: puntero que guarda la posición anterior de slow, de modo que cuando slow llega a la mitad de la lista, se usa prev para dividir la lista a la mitad
        ListNode* slow = head; //Empieza desde head (el inicio de la lista)
        ListNode* fast = head; //Empieza desde head (el inicio de la lista)
        ListNode* prev = nullptr; //De momento, es un puntero nulo
        //Mientras fast tenga un siguiente nodo...
        while (fast && fast->next) {
            prev = slow; //Prev toma el valor actual de slow
            slow = slow->next; //Slow avanza un nodo
            fast = fast->next->next; //Fast avanza dos nodos
        }
        prev->next = nullptr; // Divide la lista en dos partes
        // Ordena cada mitad de forma recursiva reutilizando el sortList, de modo que ordene tanto al lado izquierdo como al derecho.
        ListNode* left = sortList(head); //Para reutilizar sortList con la mitad izquierda de la lista
        ListNode* right = sortList(slow); //Para reutilizar sortList con la mitad derecha de la lista
        // Combina las dos mitades ordenadas usando la función merge (la cual creo yo)
        return merge(left, right);
    }

private:
    // Función auxiliar merge para fusionar dos listas ordenadas
    ListNode* merge(ListNode* l1, ListNode* l2) {
        ListNode dummy; //Nodo temporal que se usa para crear la lista fusionada
        ListNode* tail = &dummy; //Puntero que apunta a dummy para ir añadiendo los elementos ya ordenados
        //Mientras haya dos valores (l1 y l2)...
        //Donde l1 es la lista 1 y l2 es la lista 2
        while (l1 && l2) {
            //Si l1 es menor, se une a la lista 
            if (l1->val < l2->val) {
                tail->next = l1; //Lo coloca al final de la lista
                l1 = l1->next; //Se apunta al siguiente valor de la lista 1
            //Si l1 NO es menor, l2 se une a la lista.
            } else {
                tail->next = l2; //Lo coloca al final de la lista
                l2 = l2->next; //Se apunta al siguiente valor de la lista 2
            }
            //Luego de añadir el nodo l1 o l2, avanzamos tail apra que apunte al sigueinte nodo, de modo que sea el nuevo nodo final de la lista.
            tail = tail->next;
        }
        // Si queda algún elemento en l1 o l2 luego de que el bucle while termina, lo añade al final
        //Funciona de la siguiente manera: Si l1 tiene nodos restantes, entonces l2 ya es nullptr (ya se acabó y no tiene nodos restntes), por lo que, al evaluar el operador ternario (o sea, que toma tres argumentos) l1 ? l1:l2;, l1 es true (no es nullptr) y entonces el apuntador tail->next se le asigna a l1 para tomar el valor final de l1. Lo mismo pasa cuando es l2 a quien le falta un nodo, donde de nuevo usa el operador ternario donde, si es l2 a quien le falta un nodo, entonces significa que l1 es nullptr, por lo que l1 se vuelve false y el puntero tail->next apunta al final de la lista l2.
        tail->next = l1 ? l1 : l2;
        //Devuelve los nodos ya ordenados de principio (por el dummy que funcionó como ancla) hasta el final de la lista ya fusionada.
        return dummy.next;
    }
};
