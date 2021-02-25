// fnv512, a python library for 512-bit versions of the fnv-0/fnv-1/fnv-1a hashes
// Copyright (C) 2021 tweqx
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/atomic/detail/bitwise_cast.hpp>
#include <iostream>

using namespace boost::multiprecision;
using namespace boost::multiprecision::literals;
using namespace boost::atomics::detail;

constexpr uint512_t fnv_prime = 0x00000000000000000000000000000000000000000100000000000000000000000000000000000000000000000000000000000000000000000000000000000157_cppui512;

char nibble2hex(unsigned char nibble) {
  if (nibble < 10)
    return '0' + nibble;
  else
    return 'a' + nibble - 10;
}

static PyObject*
fnv0(PyObject *self, PyObject *args) {
  const char* data;
  Py_ssize_t len;

  if (!PyArg_ParseTuple(args, "s#", &data, &len))
    return NULL;

  // implementation : https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function#FNV-0_hash_(deprecated)
  uint512_t hash = 0;

  for (Py_ssize_t i = 0; i < len; i++) {
    // multiplication by 2^344 + 2^8 + 0x57
    hash *= fnv_prime;

    // xor with a byte of data
    hash ^= data[i];
  }

  char hexdigest[64 * 2];
  for (unsigned int i = 0; i < 128; i++) {
    hexdigest[127 - i] = nibble2hex(bitwise_cast<unsigned char>(hash) & 0xf);
    hash >>= 4;
  }

  return Py_BuildValue("s#", hexdigest, 128);
}
static PyObject*
fnv1(PyObject *self, PyObject *args) {
  const char* data;
  Py_ssize_t len;

  if (!PyArg_ParseTuple(args, "s#", &data, &len))
    return NULL;

  // implementation : https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function#FNV-1_hash
  uint512_t hash = 0xb86db0b1171f4416dca1e50f309990acac87d059c90000000000000000000d21e948f68a34c192f62ea79bc942dbe7ce182036415f56e34bac982aac4afe9fd9_cppui512;

  for (Py_ssize_t i = 0; i < len; i++) {
    // multiplication by 2^344 + 2^8 + 0x57
    hash *= fnv_prime;

    // xor with a byte of data
    hash ^= data[i];
  }

  char hexdigest[64 * 2];
  for (unsigned int i = 0; i < 128; i++) {
    hexdigest[127 - i] = nibble2hex(bitwise_cast<unsigned char>(hash) & 0xf);
    hash >>= 4;
  }

  return Py_BuildValue("s#", hexdigest, 128);
}
static PyObject*
fnv1a(PyObject *self, PyObject *args) {
  const char* data;
  Py_ssize_t len;

  if (!PyArg_ParseTuple(args, "s#", &data, &len))
    return NULL;

  // implementation : https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function#FNV-1a_hash
  uint512_t hash = 0xb86db0b1171f4416dca1e50f309990acac87d059c90000000000000000000d21e948f68a34c192f62ea79bc942dbe7ce182036415f56e34bac982aac4afe9fd9_cppui512;

  for (Py_ssize_t i = 0; i < len; i++) {
    // xor with a byte of data
    hash ^= data[i];

    // multiplication by 2^344 + 2^8 + 0x57
    hash *= fnv_prime;
  }

  char hexdigest[64 * 2];
  for (unsigned int i = 0; i < 128; i++) {
    hexdigest[127 - i] = nibble2hex(bitwise_cast<unsigned char>(hash) & 0xf);
    hash >>= 4;
  }

  return Py_BuildValue("s#", hexdigest, 128);
}

static PyMethodDef fnv512_methods[] = {
     {"fnv0", fnv0, METH_VARARGS, "hash function fnv-0"},
     {"fnv1", fnv1, METH_VARARGS, "hash function fnv-1"},
     {"fnv1a", fnv1a, METH_VARARGS, "hash function fnv-1a"},
     {NULL, NULL, 0, NULL}
};

static struct PyModuleDef fnv512_module =
{
    PyModuleDef_HEAD_INIT,
    "fnv512",
    NULL,
    -1,
    fnv512_methods
};

PyMODINIT_FUNC
PyInit_fnv512(void) {
     return PyModule_Create(&fnv512_module);
}
