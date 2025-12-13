/// @file  indexed_storage.hpp
/// @brief Базовый класс, реализующий хранение данных в векторе и их поиск по строковому индексу.
#ifndef STUDIES_SCHEDULE_INDEXED_STORAGE_HPP
#define STUDIES_SCHEDULE_INDEXED_STORAGE_HPP

#include <span>
#include <iterator>
#include <optional>
#include <utility>

namespace studies_schedule
{

    /// @brief  Базовый класс, реализующий простое хранение данных для случая отсутствия индекса.
    /// @tparam Data данные
    template <typename Data>
    class BasicStorage
    {
    public:
        /// @brief Получить вид только для чтения на хранимые данные.
        [[nodiscard]] constexpr auto get() const noexcept
        {
            return std::span{_data};
        }

        /// @brief Получить ссылку на элемент хранимых данных по его индексу. Неопределённое поведение в случае неверного индекса.
        template <typename Index>
        [[nodiscard]] constexpr decltype(auto) operator[](Index index) const
        {
            return get()[index];
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
    /// @tparam Data          индексируемый вектор данных
    /// @tparam IdToIndexDict словарь, отображающий идентификаторы хранимых данных в их индексы в векторе
    /// @tparam Id            преобразование, возвращающее идентификатор для объекта
    template <typename Data, typename IdToIndexDict, typename Id = DefaultId>
    class IndexedStorage
        : public BasicStorage<Data>
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
        [[nodiscard]] auto indexOf(Key const& key) const noexcept
            -> std::optional<Index>
        {
            using std::end;
            
            if (auto it = _idToIndexDict.find(key); it != end(_idToIndexDict)) {
                return it->second;
            }

            return {};
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
