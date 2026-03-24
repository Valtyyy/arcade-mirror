/*
** EPITECH PROJECT, 2026
** DlLoader
** File description:
** DlLoader
*/

#include <string>

class DlLoader {
    public:
        DlLoader(const std::string &path);
        ~DlLoader();

        void load();
        void unload();
        void *sym(const std::string & symbol) const;
        bool is_loaded() const;

    private:
        const std::string _location;
        void *_handle;
};
