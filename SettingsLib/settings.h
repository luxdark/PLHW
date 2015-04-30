#ifndef SETTINGS_H
#define SETTINGS_H

#include <fstream>
#include <iostream> // For test only
#include <map>
#include <string>
#include <vector>

#include <math.h>

class settings {
    public:
        class param {
            private:
                std :: string val = "0", tval = "", rval = "empty";
                //param(param const &);

            public:
                settings *root;
                std :: string name;
                bool rewrite = false;

                operator std::string() const;
                operator int() const;
                operator bool() const;
                operator double() const;

                param & justSetThisFolkingValue(std::string const & s);
                param & operator=(std::string const &s);
                param & operator=(int);
                param & operator=(bool);
                param & operator=(double);
                param & operator=(const char*);

                param & operator+=(std::string const &);
                param & operator+=(int);
                param & operator+=(double);

                param & operator-=(int);
                param & operator-=(double);

                param & operator*=(int);
                param & operator*=(double);

                param & operator/=(int);
                param & operator/=(double);

                param & operator|=(bool);
                param & operator&=(bool);
                bool is_empty() const;
        };

    private:
        std :: string file;
        std :: map <std :: string, param> params;

    public:
        bool ready = false;

        // Main functions

        /**
         * Construct settings store
         * and load data from file (if exists)
         * \param filename Path to file with settings
         */

        void refresh(std :: string & name, std :: string newval);

        settings(std::string const & filename);
        /**
         * Get setting value
         * \param name Setting unique identifier
         * \param def Default setting value
         * \return Stored value for given name or default value
         */
        std::string const & get(std::string const & name,
                                std::string const & def = "", std :: string res = "") const;
        /**
         * Set or replace setting value and save changes to file
         * \param name Setting unique identifier
         * \param value New setting value
         */
        void set(std::string const & name,
            std::string const & value);
        /**
         * Reset all settings
         */
        void reset();
        /**
         * Reload all settings from file
         */
        void reload();

        // Advanced fun?tions

        /**
          * Get constant setting wrapper
          * \param name Setting unique identifier
          */
        const param operator[](std::string const & name) const;
        /**
          * Get constant setting wrapper
          * \param name Setting unique identifier
          */
        param operator[](std::string const & name);
};


#endif // SETTINGS_H
