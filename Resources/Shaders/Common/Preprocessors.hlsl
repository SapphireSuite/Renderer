// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#ifndef SAPPHIRE_RENDER_SHADER_PREPROCESSORS_GUARD
#define SAPPHIRE_RENDER_SHADER_PREPROCESSORS_GUARD

/// Register view binding
#define SA_CONCAT(_rhs, _lhs) _rhs ## _lhs
#define SA_REG(_type, _id) register(SA_CONCAT(_type, _id))
#define SA_REG_SET(_type, _id, _set) register(SA_CONCAT(_type, _id), SA_CONCAT(space, _set))

#endif // SAPPHIRE_RENDER_SHADER_PREPROCESSORS_GUARD
