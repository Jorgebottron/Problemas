/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        if (!head || !head->next) return nullptr;  // Si la lista está vacía o tiene solo un nodo, no hay ciclo.
        //Aplico el algoritomo de "Tortuga y Liebre" (o en inglés, Floyd's Tortoise and Hare, por su inventor Robert W. Floyd quien lo creó a finales del año 1960), donde tengo dos punteros, donde uno va más rápido que otro.
        //Creo mis dos punteros
        ListNode *slow = head; //Slow recorrerá un nodo a la vez
        ListNode *fast = head; //Fast recorrerá dos nodos a la vez

        // Lo primero es detectar si hay un ciclo.
        while (fast && fast->next) { //Mientras que fast tenga un nodo siguiente...
            slow = slow->next; //Slow avanza un nodo
            fast = fast->next->next; //Fast avanza dos nodos

            // Si slow y fast se encuentran, hay un ciclo
            if (slow == fast) {
                // Lo siguiente es encuentrar el inicio del ciclo
                slow = head;  // Reinicia slow al inicio de la lista
                //Mientras slow sea diferente a fast, ambos se van a mover un nodo a la vez
                while (slow != fast) {
                    slow = slow->next;
                    fast = fast->next;
                }
                return slow;  // El punto de encuentro es donde inicia del ciclo
            }
        }
        //Cuando no se encontró un ciclo, el puntero fast llega al final de la lista y entonces se devuelve null
        return nullptr;
    }
};
