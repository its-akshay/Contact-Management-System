#include <iostream>
#include <string>

struct Contact {
    std::string name;
    std::string phoneNumber;
    std::string email;
    Contact* next;
};

class ContactManager {
private:
    Contact* head;

public:
    ContactManager() {
        head = nullptr;
    }

    void addContact(const std::string& name, const std::string& phoneNumber, const std::string& email) {
        Contact* newContact = new Contact;
        newContact->name = name;
        newContact->phoneNumber = phoneNumber;
        newContact->email = email;
        newContact->next = nullptr;

        if (head == nullptr) {
            head = newContact;
        }
        else {
            Contact* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newContact;
        }

        std::cout << "Contact added successfully.\n";
    }

    void viewAllContacts() {
        if (head == nullptr) {
            std::cout << "No contacts found.\n";
            return;
        }

        Contact* current = head;
        std::cout << "Contacts:\n";
        while (current != nullptr) {
            std::cout << "Name: " << current->name << "\n";
            std::cout << "Phone Number: " << current->phoneNumber << "\n";
            std::cout << "Email: " << current->email << "\n\n";
            current = current->next;
        }
    }

    Contact* searchContact(const std::string& name) {
        Contact* current = head;
        while (current != nullptr) {
            if (current->name == name) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    void deleteContact(const std::string& name) {
        if (head == nullptr) {
            std::cout << "No contacts found.\n";
            return;
        }

        if (head->name == name) {
            Contact* temp = head;
            head = head->next;
            delete temp;
            std::cout << "Contact deleted successfully.\n";
            return;
        }

        Contact* prev = head;
        Contact* current = head->next;
        while (current != nullptr) {
            if (current->name == name) {
                prev->next = current->next;
                delete current;
                std::cout << "Contact deleted successfully.\n";
                return;
            }
            prev = current;
            current = current->next;
        }

        std::cout << "Contact not found.\n";
    }

    // Destructor to free allocated memory
    ~ContactManager() {
        Contact* current = head;
        while (current != nullptr) {
            Contact* temp = current;
            current = current->next;
            delete temp;
        }
    }
};

int main() {
    ContactManager contactManager;
    int choice;
    std::string name, phoneNumber, email;

    do {
        std::cout << "Contact Management System\n";
        std::cout << "1. Add Contact\n";
        std::cout << "2. View All Contacts\n";
        std::cout << "3. Search Contact\n";
        std::cout << "4. Delete Contact\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Enter name: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            std::cout << "Enter phone number: ";
            std::getline(std::cin, phoneNumber);
            std::cout << "Enter email: ";
            std::getline(std::cin, email);
            contactManager.addContact(name, phoneNumber, email);
            break;

        case 2:
            contactManager.viewAllContacts();
            break;

        case 3:
            std::cout << "Enter the name to search: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            {
                Contact* foundContact = contactManager.searchContact(name);
                if (foundContact != nullptr) {
                    std::cout << "Contact found:\n";
                    std::cout << "Name: " << foundContact->name << "\n";
                    std::cout << "Phone Number: " << foundContact->phoneNumber << "\n";
                    std::cout << "Email: " << foundContact->email << "\n\n";
                }
                else {
                    std::cout << "Contact not found.\n";
                }
            }
            break;

        case 4:
            std::cout << "Enter the name to delete: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            contactManager.deleteContact(name);
            break;

        case 5:
            std::cout << "Exiting the program.\n";
            break;

        default:
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }

        std::cout << "\n";
    } while (choice != 5);

    return 0;
}
