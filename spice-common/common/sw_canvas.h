/* -*- Mode: C; c-basic-offset: 4; indent-tabs-mode: nil -*- */
/*
   Copyright (C) 2009 Red Hat, Inc.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, see <http://www.gnu.org/licenses/>.
*/

#ifndef H_SPICE_COMMON_SW_CANVAS
#define H_SPICE_COMMON_SW_CANVAS

#include <stdint.h>
#include <spice/macros.h>

#include "draw.h"
#include "pixman_utils.h"
#include "canvas_base.h"
#include "region.h"

SPICE_BEGIN_DECLS

SpiceCanvas *canvas_create_for_data(int width, int height, uint32_t format, uint8_t *data, int stride
                           , SpiceImageCache *bits_cache
#ifdef SW_CANVAS_CACHE
                           , SpicePaletteCache *palette_cache
#endif
                           , SpiceImageSurfaces *surfaces
                           , SpiceGlzDecoder *glz_decoder
                           , SpiceJpegDecoder *jpeg_decoder
                           , SpiceZlibDecoder *zlib_decoder
                           );


SPICE_END_DECLS

#endif
