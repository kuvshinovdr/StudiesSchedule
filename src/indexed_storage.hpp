/// @file  indexed_storage.hpp
/// @brief Базовый класс, реализующий хранение данных в векторе и их поиск по строковому индексу.
#ifndef STUDIES_SCHEDULE_INDEXED_STORAGE_HPP
#define STUDIES_SCHEDULE_INDEXED_STORAGE_HPP

#include <span>
#include <iterator>
#include <optional>
#include <type_traits>
#include <utility>

namespace studies_schedule
{

    /// Способы реализации поведения в случае попытки обращения к несуществующему элементы
    namespace invalid_index_policies
    {

        /// @brief Вернуть ссылку на статическую переменную, инициализированную по умолчанию.
        template <typename Value>
        struct ReturnEmptyValue
        {
            template <typename Index>
            constexpr auto operator()(Index&&) const noexcept
                -> Value const&
            {
                static Value const noValue;
                return noValue;
            }
        };

        /// @brief Вернуть пустой std::optional.
        template <typename Value>
        struct ReturnEmptyOptional
        {
            template <typename Index>
            constexpr auto operator()(Index&&) const noexcept
                -> std::optional<Value>
            {
                return {};
            }
        };

    }

    namespace impl
    {
        /// Извлекает тип значения контейнера. Можно переопределить.
        template <typename Container>
        struct ValueType
        {
            using type = typename Container::value_type;
        };
    }

    template <typename Container>
    using ValueType =
        typename impl::ValueType<Container>::type;

    /// @brief  Базовый класс, реализующий простое хранение данных для случая отсутствия индекса.
    /// @tparam Data данные (std::vector или его аналог)
    template <
        typename Data, 
        typename InvalidIndexPolicy = invalid_index_policies::ReturnEmptyValue<ValueType<Data>>
        >
    class BasicStorage
    {
    public:
        /// @brief Получить вид только для чтения на хранимые данные.
        [[nodiscard]] constexpr auto get() const noexcept
        {
            return std::span{_data};
        }

        /// @brief Получить ссылку на элемент хранимых данных по его индексу.
        ///
        /// В случае неверного индекса возвращает результат вызова InvalidIndexPolicy для этого индекса.
        template <typename Index>
        [[nodiscard]] constexpr decltype(auto) operator[](Index index) const
        {
            using Result = std::common_type_t<
                decltype(get()[index]), 
                decltype(InvalidIndexPolicy{}(index))
                >;
            
            auto const view { get() };

            if (static_cast<std::size_t>(index) < view.size()) {
                return static_cast<Result>(view[index]);
            }

            return static_cast<Result>(InvalidIndexPolicy{}(index));
        }

    protected:
        ~BasicStorage() = default;

        void set(Data&& data)
        {
            _data = std::move(data);
        }

    private:
        Data _data {};
    };

    /// @brief Извлечение идентификатора по умолчанию требует наличия ADL-доступной свободной функции id.
    struct DefaultId
    {
        template <typename Item>
        [[nodiscard]] constexpr decltype(auto) operator()(Item&& item) const noexcept
        {
            return id(std::forward<Item>(item));
        }
    };

    namespace impl
    {
        /// Извлекает тип значения словаря. Можно переопределить.
        template <typename Dict>
        struct MappedType
        {
            using type = typename Dict::mapped_type;
        };
    }

    /// @brief Извлечь тип значения, в который отображает свои ключи словарь Dict.
    template <typename Dict>
    using MappedType = 
        typename impl::MappedType<Dict>::type;

    /// @brief  Базовый класс, реализующий индексирование хранимого вектора с помощью словаря.
    /// @tparam Data                   индексируемый вектор данных
    /// @tparam IdToIndexDict          словарь, отображающий идентификаторы хранимых данных в их индексы в векторе
    /// @tparam DataInvalidIndexPolicy определяет действие/результат при обращении к элементу по недопустимому индексу (оператор [])
    /// @tparam DictInvalidIndexPolicy определяет действие/результат при отсутствии объекта с заданным ключом (indexOf)
    /// @tparam Id                     преобразование, возвращающее идентификатор для объекта
    template <
        typename Data, 
        typename IdToIndexDict,
        typename DataInvalidIndexPolicy = invalid_index_policies::ReturnEmptyValue<ValueType<Data>>,
        typename DictInvalidIndexPolicy = invalid_index_policies::ReturnEmptyOptional<MappedType<IdToIndexDict>>,
        typename Id                     = DefaultId
        >
    class IndexedStorage
        : public BasicStorage<Data, DataInvalidIndexPolicy>
    {
    public:
        /// @brief Тип индекса.
        using Index = MappedType<IdToIndexDict>;

        using BasicStorage<Data>::get;
        using BasicStorage<Data>::operator[];

        /// @brief Установить хранимые данные целиком, перестроить индекс.
        void set(Data&& data)
        {
            BasicStorage<Data>::set(std::move(data));
            reindex();
        }

        /// @brief Получить индекс элемента хранимых данных по ключу. В случае отсутствия элемента возвращает пустой optional.
        template <typename Key>
        [[nodiscard]] decltype(auto) indexOf(Key const& key) const noexcept
        {
            using Result = std::common_type_t<
                decltype(_idToIndexDict.find(key)->second),
                decltype(DictInvalidIndexPolicy{}(key))
                >;
            
            using std::end;
            
            if (auto it = _idToIndexDict.find(key); it != end(_idToIndexDict)) {
                return static_cast<Result>(it->second);
            }

            return static_cast<Result>(DictInvalidIndexPolicy{}(key));
        }

    protected:
        ~IndexedStorage() = default;

    private:
        IdToIndexDict _idToIndexDict  {};

        void reindex()
        {
            _idToIndexDict.clear();
            
            auto id     { Id{}    };
            auto index  { Index{} };
            
            for (auto const& item : get()) {
                _idToIndexDict.emplace(id(item), index);
                ++index;
            }
        }
    };

}

#endif//STUDIES_SCHEDULE_INDEXED_STORAGE_HPP
