/// @file  solve.hpp
/// @brief Решение задачи о расписании: связка между Task и Assignments.
#ifndef STUDIES_SCHEDULE_SOLVE_HPP
#define STUDIES_SCHEDULE_SOLVE_HPP

#include "task.hpp"
#include "assignments.hpp"

namespace studies_schedule
{

    /// @brief      Выполнить одну попытку вычисления решения задачи о расписании.
    /// @param task постановка задачи
    /// @return     набор назначений, из которых затем можно составить расписания
    /// 
    /// Результирующие назначения могут содержать элементы, назначенные на несуществующие временные слоты.
    [[nodiscard]] auto solve(Task const& task)
        -> Assignments;

    /// @brief             Проверить, что все индексы в назначениях корректны (от 0 до размера соответствующего массива в Task - 1).
    /// @param task        постановка задачи, содержащая массивы, индексы в которых записываются в назначения
    /// @param assignments проверяемые назначения (результат работы функции solve)
    /// @return            истина, если всё в порядке, иначе ложь
    [[nodiscard]] bool simpleSanityCheck(Task const& task, Assignments const& assignments);

    /// @brief             Найти неназначенные предметы.
    /// @param task        постановка задачи (содержит в том числе список всех предметов)
    /// @param assignments проверяемые назначения (результат работы функции solve)
    /// @return            набор неназначенных предметов (должен быть пуст, если solve решила задачу верно)
    [[nodiscard]] auto findUnassignedSubjects(Task const& task, Assignments const& assignments)
        -> Subjects;



}

#endif//STUDIES_SCHEDULE_SOLVE_HPP
