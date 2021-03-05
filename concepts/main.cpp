#include <fstream>
#include <iostream>
#include <concepts>
#include <type_traits>
#include <string_view>

struct Object { };

struct Member : public Object
{

    std::string_view name;

    Member(std::string_view name) : name(name) { }

};

auto &operator<<(std::ostream &stream, const Member &member) {
    return stream << "{ name: \"" << member.name << "\" }";
}

template <class _type>
concept Serializable = requires(std::ofstream stream, _type value) {
    { stream << value };
    { std::is_base_of<Object, _type>::value == true };
};

auto serialize(auto &stream, const Serializable auto &value) -> decltype(value) {
    return stream << value, value;
}

int main(int, char**) {
    std::ofstream output("output.txt");
    Member serialized = serialize(output, Member { "Boris" });
    std::cout << serialized << std::endl;
    return 0;
}
