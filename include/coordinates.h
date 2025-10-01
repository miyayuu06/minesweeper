#pragma once

namespace MS {
	struct Coordinates {
		union
		{
			float _coordinates[2];
			struct {
				float x;
				float y;
			};
		};
	};
}