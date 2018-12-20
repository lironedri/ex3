#include "CommandExpression.h"

double CommandExpression::calculate(){
    m_command->execute(m_data, m_index);
}