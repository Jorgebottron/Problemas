/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<TreeNode*> generateTrees(int n) {
        if (n == 0) return {}; // Donde si n = 0, devuelve un vector vacío
        //Usa la función privada generateTreesHelper para generar todos los árboles usando los números del 1 a n.
        //Recordemos que al final se van a hacer varios árboles debido a la condición de devolver la respuesta en cualquier orden. Por eso se generarán varios árboles. 
        return generateTreesHelper(1, n);
    }
    
private:
//IMPORTANTE, los primeros dos casos trabajan con un orden Inorder (rama izquierda, nodo, rama derecha), el tercer, cuarto y quinto caso trabajan con un orden Preorder (Nodo, rama izquierda, rama derecha)
    vector<TreeNode*> generateTreesHelper(int start, int end) {
        //Vector para guardar todos los árboles que se van a hacer
        vector<TreeNode*> trees;
        //Si start es mayor que end, se le agrega al vector del árbol un puntero nulo indicando que no hay ningún nodo en ese rango.
        //NOTA: como se usa un método recursivo, esta parte resulta no muy útil al principio, pero si para después contando que no haya más ramas, donde mínimo se tiene que poner que es una rama nula para seguir creando el árbol completo
        if (start > end) {
            trees.push_back(nullptr); // Si no hay números en la izquierda, devuelve un árbol nulo
            return trees;//Devuelve que, por lo menos en esa rama, hay un árbol vacío
        }

        //Itera sobre cada número del rango actual, de modo que en ese momento se le considera una raíz.
        for (int i = start; i <= end; i++) {
            //Para crear todos los subárboles tanto a la izquierda como a la derecha
            vector<TreeNode*> leftSubtrees = generateTreesHelper(start, i - 1); //Subárbol izquierdo
            vector<TreeNode*> rightSubtrees = generateTreesHelper(i + 1, end); //Subárbol derecho
            
            // Para combinar los árboles derechos e izquierdos según cual sea su raíz
            //Se crea un bucle basado en rango (for (TreeNode* left : leftSubtrees) o también for (TreeNode* right : rightSubtrees)), donde usamos estos ciclos for anidados para crear todas las ocombinaciones posibles tanto en los subárboles izquierdos como derechos. Luego, combina ambos árboles (izquierdo y derecho) para volverlo un único árbol según cual sea su raíz.
            //Donde: 
                //TreeNode left* es un puntero que apunta a cada elemento de leftSubtrees
                // : leftSubtrees indica que el bucle recorrerá cada elemento del vector leftSubtrees
            //leftSubtrees es un vector que contiene todos los posibles árboles izquierdos cuando i es la raíz.Lo mismo pasa con la derecha pero con los árboles de la derecha.
            for (TreeNode* left : leftSubtrees) {
                for (TreeNode* right : rightSubtrees) {
                    TreeNode* root = new TreeNode(i); //Para que con cada fusión de las ramas izquierda y derecha se cree un nuevo nodo que funcione como la raíz.
                    root->left = left; // Se le asigna a root su respectivo árbol izquierdo de esta iteración
                    root->right = right; // Se le asigna a root su respectivo árbol derecho de esta iteración
                    trees.push_back(root); // Se añade esta versión del árbol al vector de la lista de los diferentes árboles que se pueden crear.
                }
            }
        }
        return trees; //Devuelve el vector de todos los árboles posibles generados.
    }
};
