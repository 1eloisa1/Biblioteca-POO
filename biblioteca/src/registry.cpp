#include "registry.hpp"
#include "livro.hpp"
#include "revista.hpp"

// Q1 (A): Instanciações explícitas dos templates para os tipos do domínio
template class Registry<Livro>;
template class Registry<Revista>;