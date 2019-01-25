// Unless explicitly stated otherwise all files in this repository are licensed
// under the Apache License Version 2.0.
// This product includes software developed at Datadog (https://www.datadoghq.com/).
// Copyright 2019 Datadog, Inc.
#ifndef DATADOG_AGENT_SIX_THREE_H
#define DATADOG_AGENT_SIX_THREE_H
#include <vector>
#include <map>
#include <string>

#include <six.h>
#include <Python.h>

class Three: public Six {
public:
    Three(): _modules(), _pythonHome(NULL) {};
    ~Three();

    void init(const char* pythonHome);
    void addModuleFunction(const char* module, const char* funcName,
                           void* func, MethType t);

    // const API
    bool isInitialized() const;
    const char* getPyVersion() const;
    int runSimpleFile(const char* path) const;
    SixPyObject* getNone() const { return reinterpret_cast<SixPyObject*>(Py_None); }

private:
    typedef std::vector<PyMethodDef> PyMethods;
    typedef std::map<std::string, PyMethods> PyModules;

    PyModules _modules;
    wchar_t *_pythonHome;
};

#ifdef __cplusplus
extern "C" {
#endif

    extern Six* create()
    {
        return new Three();
    }

    extern void destroy(Six* p)
    {
        delete p;
    }

#ifdef __cplusplus
}
#endif
#endif
