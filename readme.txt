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

