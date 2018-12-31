#include "CommandExpression.h"

double CommandExpression::calculate(){
    return m_command->execute(m_data, m_index);
}