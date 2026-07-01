#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

// ================= ITEM (BST) =================

struct Item {
    int id;
    string name;
    int power;
};

struct Node {
    Item data;
    Node* left;
    Node* right;

    Node(Item i) {
        data = i;
        left = right = NULL;
    }
};

class BST {
    Node* root = NULL;

    Node* insert(Node* r, Item i) {
        if (!r) return new Node(i);

        if (i.id < r->data.id)
            r->left = insert(r->left, i);
        else
            r->right = insert(r->right, i);

        return r;
    }

    Node* search(Node* r, int id) {
        if (!r) return NULL;
        if (r->data.id == id) return r;

        if (id < r->data.id)
            return search(r->left, id);

        return search(r->right, id);
    }

public:
    void add(Item i) {
        root = insert(root, i);
    }

    Item* find(int id) {
        Node* r = search(root, id);
        if (r) return &r->data;
        return NULL;
    }
};

// ================= MONSTER (PRIORITY QUEUE) =================

struct Monster {
    string name;
    int power;
};

struct cmp {
    bool operator()(Monster a, Monster b) {
        return a.power < b.power; // boss mạnh lên trước
    }
};

// ================= GAME =================

class Game {
    BST items;
    vector<Item> inventory;
    queue<string> missions;
    stack<string> history;
    priority_queue<Monster, vector<Monster>, cmp> monsters;

    int score = 0;
    int level = 1;

public:

    Game() {
        // Missions
        missions.push("Find weapon");
        missions.push("Hack system");
        missions.push("Defeat enemies");
        missions.push("Survive waves");

        // Monsters (boss priority)
        monsters.push({ "Drone", 10 });
        monsters.push({ "Robot Guard", 30 });
        monsters.push({ "Cyber Tank", 60 });
        monsters.push({ "AI Boss", 100 });
    }

    // ================= MENU =================
    void menu() {
        cout << "\n===== NEON CITY SURVIVOR =====\n";
        cout << "Level: " << level << " | Score: " << score << "\n";
        cout << "1. Do Mission\n";
        cout << "2. Fight Monster\n";
        cout << "3. Pick Item\n";
        cout << "4. Undo Action\n";
        cout << "5. Show Inventory\n";
        cout << "6. Search Item (BST)\n";
        cout << "7. Level Up\n";
        cout << "0. Exit\n";
    }

    // ================= MISSION =================
    void doMission() {
        if (missions.empty()) {
            cout << "No missions left!\n";
            return;
        }

        string m = missions.front();
        missions.pop();

        cout << "Completed mission: " << m << endl;

        score += 10;
        history.push("Mission: " + m);
    }

    // ================= FIGHT =================
    void fight() {
        if (monsters.empty()) {
            cout << "No monsters left!\n";
            return;
        }

        Monster m = monsters.top();
        monsters.pop();

        cout << "Fighting: " << m.name << " (Power: " << m.power << ")\n";

        if (m.power < 30) {
            cout << "Easy win!\n";
            score += 20;
        }
        else if (m.power < 70) {
            cout << "Hard fight!\n";
            score += 50;
        }
        else {
            cout << "Boss fight!\n";
            score += 100;
        }

        history.push("Fight: " + m.name);
    }

    // ================= PICK ITEM =================
    void pickItem() {
        Item i;

        cout << "Enter item ID: ";
        cin >> i.id;

        cout << "Enter name: ";
        cin >> i.name;

        cout << "Enter power: ";
        cin >> i.power;

        items.add(i);
        inventory.push_back(i);

        cout << "Item collected!\n";

        history.push("Pick item: " + i.name);
    }

    // ================= UNDO =================
    void undo() {
        if (history.empty()) {
            cout << "Nothing to undo!\n";
            return;
        }

        cout << "Undo: " << history.top() << endl;
        history.pop();
    }

    // ================= INVENTORY =================
    void showInventory() {
        cout << "\n=== INVENTORY ===\n";

        if (inventory.empty()) {
            cout << "Empty!\n";
            return;
        }

        for (auto& i : inventory) {
            cout << i.id << " | " << i.name << " | Power: " << i.power << endl;
        }
    }

    // ================= SEARCH BST =================
    void searchItem() {
        int id;
        cout << "Enter item ID: ";
        cin >> id;

        Item* i = items.find(id);

        if (i)
            cout << "Found: " << i->name << " (Power: " << i->power << ")\n";
        else
            cout << "Item not found!\n";
    }

    // ================= LEVEL UP =================
    void levelUp() {
        level++;

        cout << "Level Up! You are now level " << level << endl;

        score += 50;

        history.push("Level Up");
    }
};

// ================= MAIN =================

int main() {
    Game g;

    int c;

    do {
        g.menu();

        cout << "Choice: ";
        cin >> c;

        switch (c) {
        case 1: g.doMission(); break;
        case 2: g.fight(); break;
        case 3: g.pickItem(); break;
        case 4: g.undo(); break;
        case 5: g.showInventory(); break;
        case 6: g.searchItem(); break;
        case 7: g.levelUp(); break;
        }

    } while (c != 0);

    cout << "\nGame Over!\nFinal Score: (check above)\n";

    return 0;
}