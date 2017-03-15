#ifndef QFE_CSEPUTILS_H__
#define QFE_CSEPUTILS_H__

#include <string>

namespace execplan
{
class ConstantColumn;
class SimpleFilter;
class ParseTree;
class SimpleColumn;
}
#include "erydbsystemcatalog.h"

namespace qfe
{
namespace utils
{
execplan::ConstantColumn* createConstCol(const std::string& valstr);

template <typename T>
execplan::ConstantColumn* createConstCol(const std::string& valstr, T val);

execplan::SimpleFilter* createSimpleFilter
				(
				boost::shared_ptr<execplan::erydbSystemCatalog>& csc,
				const execplan::erydbSystemCatalog::TableColName& tcn,
				const std::string& opstr,
				execplan::ConstantColumn* cc
				);

void appendSimpleFilter
				(
				execplan::ParseTree*& ptree,
				execplan::SimpleFilter* filter
				);

void updateParseTree(boost::shared_ptr<execplan::erydbSystemCatalog>&,
	execplan::erydbSelectExecutionPlan*&,
	execplan::SimpleColumn*,
	const std::string&, pair<int, string>);

} //namespace qfe::utils
} //namespace qfe
#endif

