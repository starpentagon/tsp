// printデバッグ
// 参考「競技プログラミングで print デバッグ」(https://naskya.net/post/0002/)
#ifndef DEBUG2_PRINT_HPP
#define DEBUG2_PRINT_HPP

#ifdef LOCAL
#define debug2(...) debug_print::multi_print2(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug2(...) ;
#endif

#ifdef LOCAL

#include <algorithm>
#include <cctype>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <string_view>
#include <type_traits>
#include <utility>

namespace debug_print {

template <class Tp>
auto has_cbegin(int) -> decltype(std::cbegin(std::declval<Tp>()), std::true_type{});
template <class Tp>
auto has_cbegin(...) -> std::false_type;
template <class Tp>
auto has_value_type(int) -> decltype(std::declval<typename Tp::value_type>(), std::true_type{});
template <class Tp>
auto has_value_type(...) -> std::false_type;

template <class Tp>
[[maybe_unused]] constexpr bool is_iteratable_container_v = decltype(has_cbegin<Tp>(int{}))::value;
template <class Tp>
[[maybe_unused]] constexpr bool is_container_v = decltype(has_value_type<Tp>(int{}))::value || is_iteratable_container_v<Tp>;

template <>
[[maybe_unused]] constexpr bool is_iteratable_container_v<std::string_view> = false;
template <>
[[maybe_unused]] constexpr bool is_container_v<std::string_view> = false;
#if (defined _GLIBCXX_STRING) || (defined _LIBCPP_STRING)
template <>
[[maybe_unused]] constexpr bool is_iteratable_container_v<std::string> = false;
template <>
[[maybe_unused]] constexpr bool is_container_v<std::string> = false;
#endif

template <class Tp, class... Ts>
struct first_element {
   using type = Tp;
};
template <class... Ts>
using first_t = typename first_element<Ts...>::type;

template <class Tp, std::enable_if_t<!decltype(has_value_type<Tp>(int{}))::value, std::nullptr_t> = nullptr>
auto check_elem(int) -> decltype(*std::cbegin(std::declval<Tp>()));
template <class Tp, std::enable_if_t<decltype(has_value_type<Tp>(int{}))::value, std::nullptr_t> = nullptr>
auto check_elem(int) -> typename Tp::value_type;
template <class Tp>
auto check_elem(...) -> void;

template <class Tp>
using elem_t = decltype(check_elem<Tp>(int{}));

template <class Tp>
[[maybe_unused]] constexpr bool is_multidim_container_v = is_container_v<Tp> && is_container_v<elem_t<Tp>>;

template <class Tp>
std::enable_if_t<!is_container_v<Tp>> out2(const Tp&);
void out2(const char&);
void out2(const char*);
void out2(const std::string_view&);

#if (defined _GLIBCXX_STRING) || (defined _LIBCPP_STRING)
void out2(const std::string&);
#endif

#ifdef __SIZEOF_INT128__
void out2(const __int128&);
void out2(const unsigned __int128&);
#endif

template <class Tp1, class Tp2>
void out2(const std::pair<Tp1, Tp2>&);

#if (defined _GLIBCXX_TUPLE) || (defined _LIBCPP_TUPLE)
template <class... Ts>
void out2(const std::tuple<Ts...>&);
#endif

#if (defined _GLIBCXX_STACK) || (defined _LIBCPP_STACK)
template <class... Ts>
void out2(std::stack<Ts...>);
#endif

#if (defined _GLIBCXX_QUEUE) || (defined _LIBCPP_QUEUE)
template <class... Ts>
void out2(std::queue<Ts...>);
template <class... Ts>
void out2(std::priority_queue<Ts...>);
#endif

template <class C>
std::enable_if_t<is_iteratable_container_v<C>> out2(const C&);

template <class Tp>
std::enable_if_t<!is_container_v<Tp>> out2(const Tp& arg) {
   std::cerr << arg;
}

void out2(const char& arg) {
   std::cerr << '\'' << arg << '\'';
}

void out2(const char* arg) {
   std::cerr << '\"' << arg << '\"';
}

void out2(const std::string_view& arg) {
   std::cerr << '\"' << arg << '\"';
}

#if (defined _GLIBCXX_STRING) || (defined _LIBCPP_STRING)
void out2(const std::string& arg) {
   std::cerr << '\"' << arg << '\"';
}
#endif

#ifdef __SIZEOF_INT128__
void out2(const __int128& arg) {
   int sign = (arg < 0) ? (-1) : 1;
   if (sign == -1)
      std::cerr << '-';
   __int128 base = sign;
   while (sign * arg >= sign * base * 10)
      base *= 10;
   while (base) {
      std::cerr << static_cast<char>('0' + (arg / base % 10));
      base /= 10;
   }
}

void out2(const unsigned __int128& arg) {
   unsigned __int128 base = 1;
   while (arg >= base * 10)
      base *= 10;
   while (base) {
      std::cerr << static_cast<char>('0' + (arg / base % 10));
      base /= 10;
   }
}
#endif

template <class Tp1, class Tp2>
void out2(const std::pair<Tp1, Tp2>& arg) {
   std::cerr << '(';
   out2(arg.first);
   std::cerr << ", ";
   out2(arg.second);
   std::cerr << ')';
}

#if (defined _GLIBCXX_TUPLE) || (defined _LIBCPP_TUPLE)
template <class T, std::size_t... Is>
void print_tuple(const T& arg, std::index_sequence<Is...>) {
   static_cast<void>(((std::cerr << (Is == 0 ? "" : ", "), out2(std::get<Is>(arg))), ...));
}

template <class... Ts>
void out2(const std::tuple<Ts...>& arg) {
   std::cerr << '(';
   print_tuple(arg, std::make_index_sequence<sizeof...(Ts)>());
   std::cerr << ')';
}
#endif

#if (defined _GLIBCXX_STACK) || (defined _LIBCPP_STACK)
template <class... Ts>
void out2(std::stack<Ts...> arg) {
   if (arg.empty()) {
      std::cerr << "<empty stack>";
      return;
   }
   std::cerr << "[ ";
   while (!arg.empty()) {
      out2(arg.top());
      std::cerr << ' ';
      arg.pop();
   }
   std::cerr << ']';
}
#endif

#if (defined _GLIBCXX_QUEUE) || (defined _LIBCPP_QUEUE)
template <class... Ts>
void out2(std::queue<Ts...> arg) {
   if (arg.empty()) {
      std::cerr << "<empty queue>";
      return;
   }
   std::cerr << "[ ";
   while (!arg.empty()) {
      out2(arg.front());
      std::cerr << ' ';
      arg.pop();
   }
   std::cerr << ']';
}
template <class... Ts>
void out2(std::priority_queue<Ts...> arg) {
   if (arg.empty()) {
      std::cerr << "<empty priority_queue>";
      return;
   }
   std::cerr << "[ ";
   while (!arg.empty()) {
      out2(arg.top());
      std::cerr << ' ';
      arg.pop();
   }
   std::cerr << ']';
}
#endif

template <class Container>
std::enable_if_t<is_iteratable_container_v<Container>> out2(const Container& arg) {
   if (std::distance(std::cbegin(arg), std::cend(arg)) == 0) {
      std::cerr << "<empty container>";
      return;
   }
   std::cerr << "[ ";
   std::for_each(std::cbegin(arg), std::cend(arg), [](const elem_t<Container>& elem) {
      out2(elem);
      std::cerr << ' ';
   });
   std::cerr << ']';
}

template <class Tp>
std::enable_if_t<!is_multidim_container_v<Tp>>
print(std::string_view name, const Tp& arg) {
   std::cerr << name << ": ";
   out2(arg);
   if constexpr (is_container_v<Tp>)
      std::cerr << '\n';
}

template <class Tp>
std::enable_if_t<is_multidim_container_v<Tp>>
print(std::string_view name, const Tp& arg) {
   std::cerr << name << ": ";
   if (std::distance(std::cbegin(arg), std::cend(arg)) == 0) {
      std::cerr << "<empty multidimensional container>\n";
      return;
   }
   std::for_each(std::cbegin(arg), std::cend(arg),
                 [&name, is_first_elem = true](const elem_t<Tp>& elem) mutable {
                    if (is_first_elem)
                       is_first_elem = false;
                    else
                       for (std::size_t i = 0; i < name.length() + 2; i++)
                          std::cerr << ' ';
                    out2(elem);
                    std::cerr << '\n';
                 });
}

template <class Tp, class... Ts>
void multi_print2(std::string_view names, const Tp& arg, const Ts&... args) {
   if constexpr (sizeof...(Ts) == 0) {
      names.remove_suffix(
          std::distance(
              names.crbegin(),
              std::find_if_not(names.crbegin(), names.crend(),
                               [](const char c) { return std::isspace(c); })));
      print(names, arg);
      if constexpr (!is_container_v<Tp>)
         std::cerr << '\n';
   } else {
      std::size_t comma_pos = 0;

      for (std::size_t i = 0, paren_depth = 0, inside_quote = false; i < names.length(); i++) {
         if (!inside_quote && paren_depth == 0 && i > 0 && names[i - 1] != '\'' && names[i] == ',') {
            comma_pos = i;
            break;
         }
         if (names[i] == '\"') {
            if (i > 0 && names[i - 1] == '\\') continue;
            inside_quote ^= true;
         }
         if (!inside_quote && names[i] == '(' && (i == 0 || names[i - 1] != '\''))
            paren_depth++;
         if (!inside_quote && names[i] == ')' && (i == 0 || names[i - 1] != '\''))
            paren_depth--;
      }

      const std::size_t first_varname_length = comma_pos - std::distance(
                                                               names.crend() - comma_pos,
                                                               std::find_if_not(
                                                                   names.crend() - comma_pos, names.crend(),
                                                                   [](const char c) { return std::isspace(c); }));
      print(names.substr(0, first_varname_length), arg);

      if constexpr (!is_container_v<Tp>) {
         if constexpr (is_container_v<first_t<Ts...>>)
            std::cerr << '\n';
         else
            std::cerr << " | ";
      }

      const std::size_t next_varname_begins_at = std::distance(
          names.cbegin(),
          std::find_if_not(
              names.cbegin() + comma_pos + 1, names.cend(),
              [](const char c) { return std::isspace(c); }));
      names.remove_prefix(next_varname_begins_at);

      multi_print2(names, args...);
   }
}
}  // namespace debug_print
#endif
#endif  // DEBUG2_PRINT_HPP
