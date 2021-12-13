meta functions and classes for json serialization - deserialization
@author spyros tsimboulis



  ┌─────────────────────────────────────────────────────────┐
  │                                                         │
  │                                                         │
  │                                                         │
  │   ┌───────►   map of key values  ─────────────────┐     │
  │   │                                               │     │
  │   │                                               ▼     │
  ▼   │                                                     │
 json ├───────►   list           ───────────►    for each value
      │
      │
      │
      └───────►  simple value



In a nutshell, the repo is a combination of :

ideas borrowed from CppCon 2014 Walter E. Brown "Modern Template Metaprogramming: A Compendium"

the C++ concept of " pointer to member "

the simple structure of json objects

In order to use it, in the C++ class / struct we add a public static constexpr member " properties ". Then we can call from - to json functions that works in a natural way and in an arbitrary depth and combination of objects.
