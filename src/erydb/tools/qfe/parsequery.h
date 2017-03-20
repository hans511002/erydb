#ifndef QFE_PARSEQUERY_H__
#define QFE_PARSEQUERY_H__

#include <unistd.h>
#include <string>

#include "erydbselectexecutionplan.h"

namespace qfe
{

execplan::erydbSelectExecutionPlan* parseQuery(const std::string&, uint32_t);

}

#endif
