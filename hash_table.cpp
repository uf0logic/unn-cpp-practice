#include <iostream>
#include <string>

constexpr int TABLE_CAPACITY = 100;

using namespace std;

class HashTable {

    // ── запись студента ──────────────────────────────────────────────
    struct Record {
        const int id;
        string fullname;
        int age;
        bool active = true;

        Record(int _id, const string& _name, int _age)
            : id(_id), fullname(_name), age(_age) {}

        void set_age(int _age) { age = _age; }

        int get_id()   const { return id; }
        string get_name() const { return fullname; }
        int get_age()   const { return age; }
        bool is_active() const { return active; }
        void deactivate() { active = false; }
    };

    // ── узел цепочки ─────────────────────────────────────────────────
    struct BucketNode {
        Record* rec;
        BucketNode* next = nullptr;

        explicit BucketNode(Record* _rec) : rec(_rec) {}
        ~BucketNode() { delete rec; }

        Record* get_record() const { return rec; }
        BucketNode* get_next() const { return next; }
        void set_next(BucketNode* p) { next = p; }
    };

    // ── хэш-таблица ──────────────────────────────────────────────────
    BucketNode* buckets[TABLE_CAPACITY] = { nullptr };
    int count = 0;
    int next_id = 1;

public:
    HashTable() = default;
    ~HashTable() = default;
    HashTable(const HashTable&) = delete;
    HashTable& operator=(const HashTable&) = delete;

    void clear() {
        for (int i = 0; i < TABLE_CAPACITY; ++i) {
            BucketNode* cur = buckets[i];
            while (cur) {
                BucketNode* nxt = cur->get_next();
                delete cur;
                cur = nxt;
            }
            buckets[i] = nullptr;
        }
        count = 0;
        next_id = 1;
    }

    // ── public API ───────────────────────────────────────────────────
    bool add_student(const string& _name, int _age) {
        unsigned idx = hash_key(_name);
        Record* existing = find_record(idx, _name);

        if (existing != nullptr) {
            if (!existing->is_active()) {
                existing->deactivate();
                existing->set_age(_age);
                existing->active = true;
                return true;
            }
            return false;               // already exists and active
        }

        Record* rec = new Record(next_id++, _name, _age);
        BucketNode* node = new BucketNode(rec);
        node->set_next(buckets[idx]);
        buckets[idx] = node;
        ++count;
        return true;
    }

    bool remove_student(const string& _name) {
        unsigned idx = hash_key(_name);
        BucketNode* cur = buckets[idx];

        while (cur != nullptr) {
            if (cur->get_record()->get_name() == _name
                    && cur->get_record()->is_active()) {
                cur->get_record()->deactivate();
                --count;
                return true;
            }
            cur = cur->get_next();
        }
        return false;
    }

    void query_by_name(const string& _name) const {
        unsigned idx = hash_key(_name);
        Record* rec = find_record(idx, _name);

        if (rec != nullptr && rec->is_active()) {
            cout << "  Found -> ID=" << rec->get_id()
                 << ", Name=" << rec->get_name()
                 << ", Age=" << rec->get_age() << endl;
        } else {
            cout << "  Student \"" << _name << "\" not found." << endl;
        }
    }

    void print_all() const {
        cout << "╔══════════════════════════════════════════════════╗" << endl;
        cout << "║              All Students Table                  ║" << endl;
        cout << "╚══════════════════════════════════════════════════╝" << endl;

        for (int i = 0; i < TABLE_CAPACITY; ++i) {
            BucketNode* cur = buckets[i];
            while (cur != nullptr) {
                Record* rec = cur->get_record();
                if (rec->is_active()) {
                    cout << "  Bucket[" << i << "]  "
                         << "ID=" << rec->get_id()
                         << ", Name=" << rec->get_name()
                         << ", Age=" << rec->get_age() << endl;
                }
                cur = cur->get_next();
            }
        }
    }

    int size() const { return count; }

private:
    Record* find_record(unsigned idx, const string& _name) const {
        BucketNode* cur = buckets[idx];
        while (cur != nullptr) {
            if (cur->get_record()->get_name() == _name) {
                return cur->get_record();
            }
            cur = cur->get_next();
        }
        return nullptr;
    }

    static unsigned hash_key(const string& key) {
        // Функция Гроувера — классическая polynomial rolling hash
        unsigned hash = 0;
        for (char ch : key) {
            hash = (hash * 31) + static_cast<unsigned>(ch);
        }
        return hash % TABLE_CAPACITY;
    }
};

// ── main ────────────────────────────────────────────────────────────
int main() {
    HashTable table;

    // Демонстрация работы
    table.add_student("Ivanov", 21);
    table.add_student("Petrov", 23);
    table.add_student("Sidorova", 20);
    table.add_student("Kuznetsov", 22);

    table.print_all();
    cout << "Total students: " << table.size() << endl;

    cout << endl;
    table.query_by_name("Petrov");
    table.query_by_name("Nonexistent");

    cout << endl;
    table.remove_student("Sidorova");
    cout << "After removal, total: " << table.size() << endl;

    table.print_all();

    return 0;
}
