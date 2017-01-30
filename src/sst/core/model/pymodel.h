// -*- c++ -*-

// Copyright 2009-2016 Sandia Corporation. Under the terms
// of Contract DE-AC04-94AL85000 with Sandia Corporation, the U.S.
// Government retains certain rights in this software.
//
// Copyright (c) 2009-2016, Sandia Corporation
// All rights reserved.
//
// This file is part of the SST software package. For license
// information, see the LICENSE file in the top level directory of the
// distribution.


#ifndef SST_CORE_MODEL_PYTHON
#define SST_CORE_MODEL_PYTHON

// This only works if we have Python defined from configure, otherwise this is
// a compile time error.
#ifdef SST_CONFIG_HAVE_PYTHON

#include <map>
#include <string>
#include <sstream>
#include <vector>

#include <sst/core/model/sstmodel.h>
#include <sst/core/config.h>
#include <sst/core/rankInfo.h>
#include <sst/core/output.h>

using namespace SST;

namespace SST {

class SSTPythonModelDefinition : public SSTModelDescription {

	public:
		SSTPythonModelDefinition(const std::string script_file, int verbosity, Config* config, int argc, char **argv);
		SSTPythonModelDefinition(const std::string script_file, int verbosity, Config* config);
		virtual ~SSTPythonModelDefinition();

		ConfigGraph* createConfigGraph();

	protected:
		void initModel(const std::string script_file, int verbosity, Config* config, int argc, char** argv);
		std::string scriptName;
		Output* output;
		Config* config;
		ConfigGraph *graph;
        char *namePrefix;
        size_t namePrefixLen;
        std::vector<size_t> nameStack;


	public:  /* Public, but private.  Called only from Python functions */
		Config* getConfig(void) const { return config; }
		//ConfigGraph* getConfigGraph(void) const { return graph; }
		Output* getOutput() const { return output; }
        ConfigComponent& addComponent(const char *name, const char *type) {
            return graph->addComponent(name, type);
        }
        ConfigComponent& findComponent(ComponentId_t id) const {
            return graph->getComponent(id);
        }
        ComponentId_t findComponentByName(const char *name) const {
            return graph->getComponentByName(name);
        }

        void addLink(ComponentId_t id, const char *name, const char *port, const char *latency, bool no_cut) const {graph->addLink(id, name, port, latency, no_cut); }

        void pushNamePrefix(const char *name);
        void popNamePrefix(void);
        char* addNamePrefix(const char *name) const;

        void setStatisticOutput(const char* Name) { graph->setStatisticOutput(Name); }
        void addStatisticOutputParameter(const char* param, const char* value) { graph->addStatisticOutputParameter(param, value); }
        void setStatisticLoadLevel(uint8_t loadLevel) { graph->setStatisticLoadLevel(loadLevel); }

        void enableStatisticForAllComponents(const char*  statname) const { graph->enableStatisticForAllComponents(statname); }
        void enableStatisticForComponentType(const char*  comptype, const char*  statname) const  { graph->enableStatisticForComponentType(comptype, statname); }

        void addStatisticParameterForAllComponents(const char* statname, const char* param, const char* value) { graph->addStatisticParameterForAllComponents(statname, param, value); }
        void addStatisticParameterForComponentType(const char*  comptype, const char* statname, const char* param, const char* value) { graph->addStatisticParameterForComponentType(comptype, statname, param, value); }
};

}

#endif

#endif
