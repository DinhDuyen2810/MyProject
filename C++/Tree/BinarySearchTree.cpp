#include <iostream>
using namespace std;
typedef struct TREENODE
{
    float data;
    int frequency;
    struct TREENODE* leftChild;
    struct TREENODE* rightChild;
}Treenode;
Treenode* createNewNode(float data) // tạo nút mới
{
    Treenode* newNode = new Treenode;
    newNode->data = data;
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;
    return newNode;
}
void insertTreeNode(Treenode* root ,float data) // thêm 1 nút vào cây
{
Treenode* newNode = createNewNode(data);
Treenode* temp = root;
while(1){
    if(temp->data == newNode->data){
        temp->frequency++;
        return;
    }
    if(temp->data > newNode->data){
        if(temp->leftChild == NULL){
            temp->leftChild = newNode;
            return;
        }
        temp = temp->leftChild;
    } else {
        if(temp->rightChild == NULL){
            temp->rightChild = newNode;
            return;
        }
        temp = temp->rightChild;
    }
}
}
void inOrderTravesal(Treenode* root) // duyệt theo thứ tự giữa
{
    if(root == NULL){
        return;
    } 
    inOrderTravesal(root->leftChild);
    cout << root->data << " ";
    inOrderTravesal(root->rightChild);
}
void makeBST(Treenode* root) // tạo cây
{
    insertTreeNode(root, 30);
    insertTreeNode(root, 41);
    insertTreeNode(root, 34);
    insertTreeNode(root, 50);
    insertTreeNode(root, 17);
    insertTreeNode(root, 23);
    insertTreeNode(root, 19);
    insertTreeNode(root, 7);
    insertTreeNode(root, 1);
    insertTreeNode(root, 15);
}
Treenode* findNode(Treenode* root, float data) // tìm nút có nhãn data ko đệ quy
{
    Treenode* temp = root;
    while(temp != NULL){
        if(temp->data == data){
            return temp;
        } else if(temp->data < data){
            temp = temp->rightChild;
        } else {
            temp = temp->leftChild;
        }
    }
    cout << "Khong tim thay " << data;
    return NULL;
}
Treenode* findNode2(Treenode* root, float data) // tìm nút có nhãn data có đệ quy
{
    if(root == NULL || root->data == data){
        return root;
    }
    Treenode* temp = findNode2(root->leftChild, data);
    if(temp != NULL){
        return temp;
    }
    return findNode2(root->rightChild, data);
}
Treenode* findDad(Treenode* root, float data) // tìm nút cha của nút p khác root
{
    Treenode* temp = root;
    while(temp != NULL){
        if((temp->leftChild != NULL && temp->leftChild->data == data) || 
           (temp->rightChild != NULL && temp->rightChild->data == data)){
            return temp;
        }
        if(temp->data > data){
            temp = temp->leftChild;
        } else {
            temp = temp->rightChild;
        }
    }
    return NULL;
}
int height(Treenode* root) // chiều cao của nút p
{
    if(root == NULL) return -1;
    return 1 + ((height(root->leftChild) > height(root->rightChild)) 
            ? height(root->leftChild) : height(root->rightChild));
}
int depth(Treenode* root, float data) // tính độ sâu của nút không đệ quy
{
    if(root == NULL){
        return -1;
    }
    int deep = 0;
    Treenode* temp = root;
    while(temp != NULL){
        if(temp->data == data){
            return deep;
        } else if(temp->data < data){
            temp = temp->rightChild;
        } else {
            temp = temp->leftChild;
        }
        deep++;
    }
    cout << "Khong co nut " << data << endl;
    return -1;
}
int depth2(Treenode* root, float data) // tính độ sâu của nút có đệ quy
{
    if(root == NULL){
        return -1;
    }
    if(root->data == data){
        return 0;
    }
    int left = depth2(root->leftChild, data);
    if(left >= 0){
        return 1 + left;
    }
    int right = depth2(root->rightChild, data);
    if(right >= 0){
        return 1 + right;
    }
    return -1;
}
int maxLeaf(Treenode* root) // tính Lá lớn nhất với cây khác rỗng
{
    Treenode* temp = root;
    while(temp->rightChild != NULL){
        temp = temp->rightChild;
    }
    cout << endl << "La lon nhat la: ";
    return temp->data;
}
bool checkAncestor(Treenode* root, Treenode* child) // kiểm tra root có là tổ tiên của child ko
{
    if(root == NULL){
        return false;
    }
    if(root == child){
        return true;
    }
    return checkAncestor(root->leftChild, child) || checkAncestor(root->rightChild, child); 
}
bool isLeaf(Treenode* p) // check có phải lá không
{
    if(p->leftChild == NULL && p->rightChild == NULL){
        return true;
    }
    return false;
}
bool isMissingChild(Treenode* p) // check có phải nút 1 con không
{
    if(p->leftChild == NULL || p->rightChild == NULL){
        return true;
    }
    return false;
}
Treenode* commonAncestor(Treenode* root, Treenode* child1, Treenode* child2) // tổ tiên chung
{
    if(checkAncestor(child1, child2) || checkAncestor(child2, child1))
    {
        Treenode* temp;
        if(checkAncestor(child1, child2)){
            temp = child1;
        } else {
            temp = child2;
        }
        Treenode* tmp = root;
        if(tmp->data == temp->data){
            cout << "Khong co to tin chung vi co mot nut la root";
            return NULL;
        }
        while(tmp->data > temp->data){
            if(tmp->leftChild->data == temp->data){
                return tmp;
            }
            tmp = tmp->leftChild;
        }
        while(tmp->data < temp->data){
            if(tmp->rightChild->data == temp->data){
                return tmp;
            }
            tmp = tmp->rightChild;
        }
    } else {
        Treenode* temp = root;
        int max = (child1->data > child2->data) ? child1->data : child2->data;
        int min = (child1->data < child2->data) ? child1->data : child2->data;
        while(temp->data < min || temp->data > max){
            if(temp->data < min){
                temp = temp->rightChild;
            }
            if(temp->data > max){
                temp = temp->leftChild;
            }
        }
        return temp;
    }
    return NULL;
}
void removeNode1(Treenode* root, Treenode* p){ // xóa nút lá hoặc con khuyết
    if(isLeaf(p)){
        if(findDad(root, p->data)->leftChild == p){
            findDad(root, p->data)->leftChild = NULL;
        } else {
            findDad(root, p->data)->rightChild = NULL;
        }
        delete p;
    } else {
        Treenode* tempDad = findDad(root, p->data);
        if(findDad(root, p->data)->leftChild == p){
            if(p->leftChild != NULL){
                tempDad->leftChild = p->leftChild;
            } else {
                tempDad->leftChild = p->rightChild;
            }
        } else {
            if(p->leftChild != NULL){
                tempDad->rightChild = p->leftChild;
            } else {
                tempDad->rightChild = p->rightChild;
            }
        }
        delete p;
    }
}
void removeNode(Treenode* root, Treenode* p) // xóa nút
{
    if(isLeaf(p) || isMissingChild(p)){
        removeNode1(root, p);
    } else {
        Treenode* temp = p->leftChild;
        while(temp->rightChild != NULL){
            temp = temp->rightChild;
        }
        float tmp = temp->data;
        removeNode1(p, temp);
        p->data = tmp;
    }
}
int countNode(Treenode* root) // Đếm số nút
{
    Treenode* temp = root;
    if(root == NULL){
        return 0;
    }
    int count = 0;
    if(isLeaf(temp)){
        return 1;
    }
    temp = root->leftChild;
    if(countNode(temp) > 0){
        count = countNode(temp);
    }
    temp = root->rightChild;
    return count += countNode(temp) + 1;
}
bool isFull(Treenode* p)// kiểm tra có phải nút đầy đủ không
{
    if(p->leftChild != NULL && p->rightChild != NULL){
        return true;
    }
    return false;
}
int countFullNodes(Treenode* root)// Đếm và trả về số lượng nút đầy đủ trên cây
{
    if(root == NULL){
        return 0;
    }
    Treenode* temp = root;
    int count = 0;
    count += countFullNodes(temp->leftChild);
    count += countFullNodes(temp->rightChild);
    if(isFull(temp)){
        count ++;
    }
    return count;
}
int countLevel(Treenode* root)
{
    if(root == NULL){
        return -1;
    }
	Treenode* temp = root;
    int count = 0;
    if(countLevel(temp->leftChild) >= 0){
        count = 1 + countLevel(temp->leftChild);
    }
    if(countLevel(temp->rightChild) >= 0){
        if(count < 1 + countLevel(temp->rightChild)){
            count = 1 + countLevel(temp->rightChild);
        }
    }
    return count;
}
int isBinarySearchTree(Treenode* root)// Kiểm tra có phải cây nhị phân tìm kiếm không
{
	Treenode* temp = root;
    if(temp == NULL){
        return 1;
    }
    if(!isBinarySearchTree(temp->leftChild) || !isBinarySearchTree(temp->rightChild)){
        return 0;
    }
    if(temp->leftChild != NULL){
        if(temp->leftChild->data >= temp->data){
            return 0;
        }
    } 
    if(temp->rightChild != NULL){
        if(temp->rightChild->data <= temp->data){
            return 0;
        }
    }
    return 1;
}
int main(){
    float name;
    Treenode* root = createNewNode(25);
    Treenode* temp;

    makeBST(root);
    cout << "\ninOrder: ";
    inOrderTravesal(root);
    cout << endl;
    cout << isBinarySearchTree(root);
/*     cout << "Nhap nut ban muon them: ";
    cin >> name;
    insertTreeNode(root, name);
    cout << "inOrder: ";
    inOrderTravesal(root);

    cout << endl << "Nhap nut muon xoa: ";
    cin >> name;
    temp = findNode(root, name);
    if(temp != NULL){
        removeNode(root, temp);
    }
    cout << "inOrder: ";
    inOrderTravesal(root);

    cout << endl << "Cay co tong so nut la: " << countNode(root) << endl;

    cout << "Ban muon kiem tra ptu nao: ";
    cin >> name;
    temp = findNode(root, name);
    if(temp != NULL){
        if(temp == root){
            cout << "Nut " << name << " la root";
            if(temp->leftChild != NULL){
                cout << endl << "Con trai la " << root->leftChild->data;
            } else {
                cout << endl << "Khong co con trai" ;
            }
            if(temp->rightChild != NULL){
                cout << endl << "Con phai la " << root->rightChild->data;
            } else {
                cout << endl << "Khong co con phai" ;
            }
            cout << endl << "Do sau la " << depth(root, name);
            cout << endl << "Do cao la " << height(temp);
        } else {
            cout << "Cha cua " << name << " la " << findDad(root, name)->data << endl;
            if(isLeaf(temp)){
                cout << name << " la la";
            } else {
                if(temp->leftChild != NULL){
                    cout << endl << "Con trai la " << temp->leftChild->data;
                } else {
                    cout << endl << "Khong co con trai" ;
                }
                if(temp->rightChild != NULL){
                    cout << endl << "Con phai la " << temp->rightChild->data;
                } else {
                    cout << endl << "Khong co con phai" ;
                } 
                cout << endl << "Do sau la " << depth(root, name);
                cout << endl << "Do cao la " << height(temp);
            }
        }
    }
 */


}

                                                                                                          