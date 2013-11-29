#ifndef INCLUDED_RENDER_CAMERA_H
#define INCLUDED_RENDER_CAMERA_H

class Camera : public Singleton<Camera>
{
	glm::mat4 mView;
	glm::mat4 mInverseView;
	glm::vec2 mCenter;
	glm::vec2 mAllowedDistance;
	friend class Singleton<Camera>;
	Camera();
	Scene& mScene;
	void UpdateMatrices();
public:
	void Update();
	glm::mat4 const& GetView()const;
	glm::mat4 const& GetInverseView()const;
};

#endif//INCLUDED_RENDER_CAMERA_H
