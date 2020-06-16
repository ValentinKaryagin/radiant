#pragma once

namespace Radiant
{
	enum EVRStereoType
	{
		EVRST_LeftEye,
		EVRST_RightEye,
		EVRST_Max
	};

	enum EVRRenderTargetTextureType
	{
		EVRRTTT_Unknown,
		EVRRTTT_OpenGL,
		EVRRTTT_D3D,
		EVRRTTT_Vulkan,
		EVRRTTT_Max
	};
}
