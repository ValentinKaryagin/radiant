#include "SteamVRSystem.h"

#include "openvr.h"

namespace Radiant
{
	SteamVRSystem::SteamVRSystem()
		: VRSystem(nullptr)
		, VRCompositor(nullptr)
		, AbsoluteMatrix(Matrix::Identity)
		, OffsetMatrix(RotationMatrix(Quaternion(Math::DegsToRads(90.0f), Vector3::Forward) * Quaternion(Math::DegsToRads(90.0f), Vector3::Right)))
	{}

	SteamVRSystem::~SteamVRSystem() {}

	int32_t SteamVRSystem::Init()
	{
		vr::EVRInitError VRInitError = vr::VRInitError_None;
		VRSystem = vr::VR_Init(&VRInitError, vr::VRApplication_Scene);
		if (VRInitError != vr::VRInitError_None)
		{
			VRSystem = nullptr;
			printf("VRInit error: %s\n", vr::VR_GetVRInitErrorAsEnglishDescription(VRInitError));
			return 1;
		}
		
		VRCompositor = vr::VRCompositor();
		if (!VRCompositor)
		{
			vr::VR_Shutdown();
			VRSystem = nullptr;
			printf("VRCompositor error\n");
			return false;
		}

		uint32_t VRWidth = 0, VRHeight = 0;
		VRSystem->GetRecommendedRenderTargetSize(&VRWidth, &VRHeight);

		printf("VR recommended target size: %u %u\n", VRWidth, VRHeight);

		return 0;
	}

	void SteamVRSystem::Terminate()
	{
		VRCompositor = nullptr;
		vr::VR_Shutdown();
		VRSystem = nullptr;
	}

	bool SteamVRSystem::IsInited() const
	{
		return VRSystem ? true : false;
	}

	void SteamVRSystem::TickInput(float DeltaTime)
	{
		vr::VREvent_t VREvent{};
		if (VRSystem->PollNextEvent(&VREvent, sizeof(vr::VREvent_t)))
		{
			//printf("VRDevice %u Event\n", VREvent.trackedDeviceIndex);
			/*if (VREvent.eventType == vr::VREvent_TrackedDeviceDeactivated)
			{
				//printf("VRDevice %u detached\n", VREvent.trackedDeviceIndex);
			}
			else if (VREvent.eventType == vr::VREvent_TrackedDeviceUpdated)
			{
				//printf("VRDevice %u updated\n", VREvent.trackedDeviceIndex);
			}
			else
			{
				// ?
			}*/
		}				

		vr::TrackedDevicePose_t TrackedDevicePoses[vr::k_unMaxTrackedDeviceCount]{};

		vr::EVRCompositorError CompositorError = vr::VRCompositorError_None;
		CompositorError = VRCompositor->WaitGetPoses(TrackedDevicePoses, vr::k_unMaxTrackedDeviceCount, nullptr, 0);
		if (CompositorError != vr::VRCompositorError_None)
		{
			printf("VRCompositor WaitGetPoses error: %d\n", CompositorError);
		}

		for (size_t Item = 0; Item < vr::k_unMaxTrackedDeviceCount; ++Item)
		{
			if (TrackedDevicePoses[Item].bPoseIsValid)
			{
				vr::TrackedDeviceClass DeviceClass = VRSystem->GetTrackedDeviceClass(static_cast<vr::TrackedDeviceIndex_t>(Item));
				
				if (DeviceClass == vr::TrackedDeviceClass_Invalid)
				{
					//printf("VR tracked device %llu %d\n", Item, DeviceClass);
				}
				else if (DeviceClass == vr::TrackedDeviceClass_HMD)
				{
					//printf("VR tracked device %llu %d\n", Item, DeviceClass);
					vr::HmdMatrix34_t *SteamAbsoluteMatrixPtr = &TrackedDevicePoses[Item].mDeviceToAbsoluteTracking;
					AbsoluteMatrix = Matrix(
						SteamAbsoluteMatrixPtr->m[0][0], SteamAbsoluteMatrixPtr->m[1][0], -SteamAbsoluteMatrixPtr->m[2][0], 0.0f,
						SteamAbsoluteMatrixPtr->m[0][1], SteamAbsoluteMatrixPtr->m[1][1], -SteamAbsoluteMatrixPtr->m[2][1], 0.0f,
						SteamAbsoluteMatrixPtr->m[0][2], SteamAbsoluteMatrixPtr->m[1][2], -SteamAbsoluteMatrixPtr->m[2][2], 0.0f,
						SteamAbsoluteMatrixPtr->m[0][3], SteamAbsoluteMatrixPtr->m[1][3], -SteamAbsoluteMatrixPtr->m[2][3], 1.0f).GetInverted();
				}
				else if (DeviceClass == vr::TrackedDeviceClass_Controller)
				{
					//printf("VR tracked device %llu %d\n", Item, DeviceClass);
				}
				else if (DeviceClass == vr::TrackedDeviceClass_GenericTracker)
				{
					//printf("VR tracked device %llu %d\n", Item, DeviceClass);
				}
				else if (DeviceClass == vr::TrackedDeviceClass_TrackingReference)
				{
					//printf("VR tracked device %llu %d\n", Item, DeviceClass);
				}
				else if (DeviceClass == vr::TrackedDeviceClass_DisplayRedirect)
				{
					//printf("VR tracked device %llu %d\n", Item, DeviceClass);
				}
				else
				{
					// WTF?
					//printf("VR tracked device %llu WTF?\n", Item);
				}
			}
		}				
	}

	void SteamVRSystem::Present(void *Texture, EVRStereoType StereoType, EVRRenderTargetTextureType TextureType)
	{
		// Texture settings
		vr::Texture_t VRTexture;
		VRTexture.handle		= Texture;
		if		(TextureType == EVRRenderTargetTextureType::EVRRTTT_OpenGL)	VRTexture.eType = vr::TextureType_OpenGL;
		else if	(TextureType == EVRRenderTargetTextureType::EVRRTTT_D3D)	VRTexture.eType = vr::TextureType_DirectX;
		else if	(TextureType == EVRRenderTargetTextureType::EVRRTTT_Vulkan)	VRTexture.eType = vr::TextureType_Vulkan;
		else return;
		VRTexture.eColorSpace	= vr::ColorSpace_Auto;

		// Bounds settings
		vr::VRTextureBounds_t Bounds;
		if (StereoType == EVRStereoType::EVRST_LeftEye)
		{
			Bounds.uMin = 0.0f;
			Bounds.uMax = 0.5f;
			Bounds.vMin = 1.0f;
		}
		else if (StereoType == EVRStereoType::EVRST_RightEye)
		{
			Bounds.uMin = 0.5f;
			Bounds.uMax = 1.0f;
			Bounds.vMin = 1.0f;			
		}
		else return;
		Bounds.vMax = 0.0f;

		 vr::EVRCompositorError CompositorError = VRCompositor->Submit(StereoType == EVRStereoType::EVRST_LeftEye ? vr::Eye_Left : vr::Eye_Right, &VRTexture);
		if (CompositorError != vr::VRCompositorError_None)
		{
			// TODO: Log errors
		}		

		VRCompositor->PostPresentHandoff();
	}

	void SteamVRSystem::GetTargetSize(uint32_t *Width, uint32_t *Height) const
	{
		VRSystem->GetRecommendedRenderTargetSize(Width, Height);
	}

	Matrix SteamVRSystem::GetAbsoluteMatrix() const
	{
		return AbsoluteMatrix;
	}

	Matrix SteamVRSystem::GetStereoViewMatrix(EVRStereoType Eye) const
	{
		vr::HmdMatrix34_t SteamMatrix = VRSystem->GetEyeToHeadTransform(Eye == EVRStereoType::EVRST_LeftEye ? vr::Eye_Left : vr::Eye_Right);
		return Matrix(
			SteamMatrix.m[0][0], SteamMatrix.m[1][0], -SteamMatrix.m[2][0], 0.0f,
			SteamMatrix.m[0][1], SteamMatrix.m[1][1], -SteamMatrix.m[2][1], 0.0f,
			SteamMatrix.m[0][2], SteamMatrix.m[1][2], -SteamMatrix.m[2][2], 0.0f,
			SteamMatrix.m[0][3], SteamMatrix.m[1][3], SteamMatrix.m[2][3], 1.0f).GetInverted();
	}

	Matrix SteamVRSystem::GetStereoProjectionMatrix(EVRStereoType Eye) const
	{
		vr::HmdMatrix44_t SteamMatrix = VRSystem->GetProjectionMatrix(Eye == EVRStereoType::EVRST_LeftEye ? vr::Eye_Left : vr::Eye_Right, 0.001f, 1000.0f);
		return Matrix(
			SteamMatrix.m[0][0], SteamMatrix.m[1][0], SteamMatrix.m[2][0], SteamMatrix.m[3][0],
			SteamMatrix.m[0][1], SteamMatrix.m[1][1], SteamMatrix.m[2][1], SteamMatrix.m[3][1],
			SteamMatrix.m[0][2], SteamMatrix.m[1][2], -SteamMatrix.m[2][2], -SteamMatrix.m[3][2],
			SteamMatrix.m[0][3], SteamMatrix.m[1][3], SteamMatrix.m[2][3], SteamMatrix.m[3][3]);
	}

	Matrix SteamVRSystem::GetOffsetMatrix() const
	{
		return OffsetMatrix;
	}
}
