/* Revised 4/5/2026 */
/* Revised by Brandon Zuniga */

/* Alli */
/* 03/14/2026 */

#include <Wt/Dbo/Transaction.h>
#include <Wt/Dbo/Dbo.h>
#include <chrono> //#include <Wt/WTime.h>
#include <string>
#include <memory>
#include <Wt/Dbo/backend/Sqlite3.h>
#include "databaseManagerModel.h"

namespace dbo = Wt::Dbo;

DatabaseManager::DatabaseManager():session_(Database::instance().session()){

	
}
namespace {

std::vector<std::string>
loadRolesForUser(dbo::Session& session, dbo::ptr<User> userPtr)
{
  std::vector<std::string> titles;
  if (!userPtr) {
    return titles;
  }
  dbo::collection<dbo::ptr<Role>> coll =
    session.find<Role>().where("user_id = ?").bind(userPtr.id());
  for (const dbo::ptr<Role>& r : coll) {
    titles.push_back(r->getRoleTitle());
  }
  return titles;
}

void
removeRolesForUser(dbo::Session& session, int userId)
{
  dbo::collection<dbo::ptr<Role>> coll =
    session.find<Role>().where("user_id = ?").bind(userId);
  std::vector<dbo::ptr<Role>> toRemove;
  for (const dbo::ptr<Role>& r : coll) {
    toRemove.push_back(r);
  }
  for (dbo::ptr<Role>& r : toRemove) {
    r.remove();
  }
}

} // namespace

int
DatabaseManager::addUser(User& user)
{
  dbo::Transaction t(session_);
  try {
    dbo::ptr<User> duplicate =
      session_.find<User>().where("userName = ?").bind(user.getUserName());
    if (duplicate) {
      return -1;
    }

    auto newUser = std::make_unique<User>();
    newUser->setName(user.getName());
    newUser->setUserName(user.getUserName());
    newUser->setPassHash(user.getPassHash());

    dbo::ptr<User> userPtr = session_.add(std::move(newUser));

    for (const auto& roleTitle : user.getRole()) {
      auto roleObj = std::make_unique<Role>();
      roleObj->setUser(userPtr);
      roleObj->setRoleTitle(roleTitle);
      session_.add(std::move(roleObj));
    }

    t.commit();

    int newId = userPtr.id();
    user.setID(newId);
    return newId;

  } catch (...) {
    return -2;
  }
}

int
DatabaseManager::editUser(const User& user)
{
  int userID;
  dbo::Transaction t(session_);
  dbo::ptr<User> userFound =
    session_.find<User>().where("id = ?").bind(user.getID());
  if (userFound) {
    {
      User* mod = userFound.modify();
      if (!user.getName().empty()) {
        mod->setName(user.getName());
      }
      if (!user.getUserName().empty()) {
        mod->setUserName(user.getUserName());
      }
      if (!user.getPassHash().empty()) {
        mod->setPassHash(user.getPassHash());
      }
    }
    userID = userFound.id();

    removeRolesForUser(session_, userID);
    for (const auto& roleTitle : user.getRole()) {
      auto roleObj = std::make_unique<Role>();
      roleObj->setUser(userFound);
      roleObj->setRoleTitle(roleTitle);
      session_.add(std::move(roleObj));
    }
  } else {
    userID = -1;
  }
  t.commit();
  return userID;
}

int
DatabaseManager::deleteUser(int userId)
{
  int result;
  dbo::Transaction t(session_);
  dbo::ptr<User> dbUser = session_.find<User>().where("id = ?").bind(userId);
  if (!dbUser) {
    result = -1;
  } else {
    removeRolesForUser(session_, userId);
    dbUser.remove();
    t.commit();
    result = 1;
  }
  return result;
}

User
DatabaseManager::getUserByIdentity(const std::string& username)
{
  dbo::Transaction t(session_);

  dbo::ptr<User> result =
    session_.find<User>().where("userName = ?").bind(username);
  if (result) {
    User user;
    user.setName(result->getName());
    user.setUserName(result->getUserName());
    user.setPassHash(result->getPassHash());
    user.setID(result.id());
    user.setRole(loadRolesForUser(session_, result));
    return user;
  }
  User userNotFound;
  return userNotFound;
}

std::vector<User>
DatabaseManager::getAllUsers()
{
  dbo::Transaction t(session_);
  using Users = dbo::collection<dbo::ptr<User>>;
  Users users = session_.find<User>();

  std::vector<User> userVector;
  for (const dbo::ptr<User>& user : users) {
    User newUser;
    newUser.setName(user->getName());
    newUser.setUserName(user->getUserName());
    newUser.setPassHash(user->getPassHash());
    newUser.setID(user.id());
	std::cout << "setting user id: " << user.id()<<std::endl;
    newUser.setRole(loadRolesForUser(session_, user));
    userVector.push_back(newUser);
  }
  return userVector;
}


void DatabaseManager::addRisk(const RiskItem& risk)
{
	//Same as adding a User:
	dbo::Transaction t(session_);
	
	auto newRisk = std::make_unique<RiskItem>();
	newRisk->setRiskName(risk.getRiskName());
	newRisk->setDesc(risk.getDesc());
	newRisk->setProbability(risk.getProbability());
	newRisk->setImpact(risk.getImpact());
	newRisk->setProjectID(risk.getProjectID());

	dbo::ptr<RiskItem> riskPtr = session_.add(std::move(newRisk));
	t.commit();
}


void DatabaseManager::editRisk(const RiskItem& risk)
{
	//Same idea as editUser: 
	dbo::Transaction t(session_);

	dbo::ptr<RiskItem> dbRisk = session_.find<RiskItem>().where("id=?").bind(risk.getRiskID());
	dbRisk.modify()->setRiskName(risk.getRiskName());
	dbRisk.modify()->setDesc(risk.getDesc());
	dbRisk.modify()->setProbability(risk.getProbability());
	dbRisk.modify()->setImpact(risk.getImpact());

	t.commit();
}
void DatabaseManager::deleteRisk(const RiskItem& risk)
{
	//Same idea as deleteUser:
	dbo::Transaction t(session_);
	dbo::ptr<RiskItem> result = session_.find<RiskItem>().where("id = ?").bind(risk.getRiskID());
	result.remove();
	t.commit();
}

std::vector<RiskItem> DatabaseManager::getRisksByProject(int pid) {
        dbo::Transaction t(session_);

	//For returning a collection of risks:
	using Risks = dbo::collection<dbo::ptr<RiskItem>>;
	Risks risks = session_.find<RiskItem>().where("projectID = ?").bind(pid);

	//Populate RiskItem vector and return:
	std::vector<RiskItem> riskVector;
	for (const dbo::ptr<RiskItem> &risk : risks) {
		RiskItem r;
		r.setRiskID(risk.id());
		r.setProjectID(risk->getProjectID());
		r.setRiskName(risk->getRiskName());
		r.setDesc(risk->getDesc());
		r.setProbability(risk->getProbability());
		r.setImpact(risk->getImpact());
		riskVector.push_back(r);
	}
	return riskVector;
}

RiskItem DatabaseManager::getRiskById(int rid) {
        dbo::Transaction t(session_);
        dbo::ptr<RiskItem> risk = session_.find<RiskItem>().where("id = ?").bind(rid);
	RiskItem r;
	r.setRiskID(risk.id());
	r.setProjectID(risk->getProjectID());
	r.setRiskName(risk->getRiskName());
	r.setDesc(risk->getDesc());
	r.setProbability(risk->getProbability());
	r.setImpact(risk->getImpact());
	
	return r;
}

void DatabaseManager::addProject(const Project& p)
{
	//Same as adding a User:
	dbo::Transaction t(session_);
	
	auto newProject = std::make_unique<Project>();
	newProject->setName(p.getName());
	newProject->setImpactCount(p.getImpactCount());
	newProject->setProbCount(p.getProbCount());
	newProject->setCreated(p.getCreated());
	newProject->setModified(p.getModified());
	
	dbo::ptr<Project> projectPtr = session_.add(std::move(newProject));
	t.commit();
}

void DatabaseManager::editProject(const Project& p)
{
	//Same idea as editUser: 
	dbo::Transaction t(session_);

	dbo::ptr<Project> dbProject = session_.find<Project>().where("id=?").bind(p.getID());
	dbProject.modify()->setName(p.getName());
	dbProject.modify()->setImpactCount(p.getImpactCount());
	dbProject.modify()->setProbCount(p.getProbCount());
	dbProject.modify()->setCreated(p.getCreated());
	dbProject.modify()->setModified(p.getModified());

	t.commit();
}

void DatabaseManager::deleteProject(const Project& p) {
	//Same idea as deleteUser:
	dbo::Transaction t(session_);
	dbo::ptr<Project> result = session_.find<Project>().where("id = ?").bind(p.getID());
	result.remove();
	t.commit();
}

Project DatabaseManager::getProjectByID(int id) {
        dbo::Transaction t(session_);
	//Same idea as getRiskByID:
	dbo::ptr<Project> project = session_.find<Project>().where("id = ?").bind(id);
	Project p;
	p.setName(project->getName());
	p.setImpactCount(project->getImpactCount());
	p.setProbCount(project->getProbCount());
	p.setCreated(project->getCreated());
	p.setModified(project->getModified());
	p.setID(project.id());		
	return p;
}

std::vector<Project> DatabaseManager::getAllProjects() {
	dbo::Transaction t(session_);
	using Projects = dbo::collection<dbo::ptr<Project>>;
	Projects projects = session_.find<Project>();

	std::vector<Project> projectVector;
	for (const dbo::ptr<Project>& project : projects) {
		Project p;
		p.setName(project->getName());
		p.setImpactCount(project->getImpactCount());
		p.setProbCount(project->getProbCount());
		p.setCreated(project->getCreated());
		p.setModified(project->getModified());
		p.setID(project.id());
		projectVector.push_back(p);
	}
	return projectVector;
}

void DatabaseManager::logActivity(std::chrono::system_clock::time_point time, const std::string& username, const std::string& event,
		const std::string& entity, const std::string& details) {
	//Same as adding a User:
	dbo::Transaction t(session_);
	
	auto auditLog = std::make_unique<AuditLog>(time, username, event, entity, details);
        /*
	auditLog->setTimestamp(time);
	auditLog->setUsername(username);
	auditLog->setEventType(event);
	auditLog->setEntityType(entity);
	auditLog->setDetails(details);
        */
	
	dbo::ptr<AuditLog> logPtr = session_.add(std::move(auditLog));
	t.commit();
}
