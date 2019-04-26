#pragma once
#include <glm.hpp>
#include <ext.hpp>

using glm::mat4;
using glm::vec3;
using glm::vec4;

class Camera
{
public:
	Camera(float fov, float aspectRatio, float nearF, float farF, vec3 from, vec3 to, vec3 up);


	virtual void update(float dt) = 0;

	/*
		@brief Uses four floats to create a perspective matrix and sets m_projectionTransform to the result
		@param fov: the field of view for the camera
		@param aspectRatio: the aspect ratio of the window
		@param near: the minimum distance at which an object should be rendered
		@param far: the maximum distance at which an object should be rendered
	*/
	virtual void setPerspective(float fov, float aspectRatio, float near, float far);

	/*
		@brief Uses 3 vectors to create a view matrix, then sets m_viewTransform to the result
		@param from: the location of the camera in global space
		@param to: the location the camera will be looking toward
		@param up: the local y normal relative to the camera
	*/
	virtual void setLookAt(vec3 from, vec3 to, vec3 up);

	/*
		@brief set global position to the argument position
		@param position to be set to
	*/
	virtual void setPosition(vec3 position);


	virtual mat4 getWorldTransform() { return m_worldTransform; }
	virtual mat4 getView() { return m_viewTransform; }
	virtual mat4 getProjection() { return m_projectionTransform; }
	virtual mat4 getProjectionView() { return m_projectionViewTransform; }
	virtual vec4 getPosition() { return m_worldTransform[3]; }

protected:
	mat4 m_worldTransform;
	mat4 m_viewTransform;
	mat4 m_projectionTransform;
	mat4 m_projectionViewTransform;

	/*
		@brief m_viewTransform is changed to the inverse of m_worldTransform
		@brief and then update the projection view transform
	*/
	virtual void updateProjectionViewTransform();
};

