/* Alli */
/* 3/14/2026 */
#ifndef SCALELABEL_H
#define SCALELABEL_H

#include <string>
#include <Wt/Dbo/Dbo.h>

#include "projectModel.h"

namespace dbo = Wt::Dbo;

class ScaleLabel : public dbo::Dbo<ScaleLabel> {
    private:
        int                 id;
        dbo::ptr<Project>   project;
        int                 type;
        std::string         name;
        int                 level;

    public:
        template<class Action>
        void persist(Action& a) 
        {
                dbo::belongsTo(a, project, "project");
                dbo::field(a, type, "type");
                dbo::field(a, name, "name");
                dbo::field(a, level, "level");
        }

        //Constructors
        ScaleLabel() = default; //delete;
        ScaleLabel(int i, dbo::ptr<Project> p, int t, std::string n, int l) : 
            id(i), project(p), type(t), name(n), level(l) {
        }

        //Getters
        int getId() const {
                return id;
        }
        dbo::ptr<Project> getProject() const  {
                return project;
        }
        int getType() const {
                return type;
        }
        std::string getName() const {
                return name;
        }
        int getLevel() const {
                return level;
        }

        //Setters
        void setId(int i) {
                id = i;
        }
        void setProject(dbo::ptr<Project> p) {
                project = p;
        }
        void setType(int t) {
                type = t;
        }
        void setName(std::string n) {
                name = n;
        }
        void setLevel(int l) {
                level = l;
        }
};

#endif //SCALELABEL_H
