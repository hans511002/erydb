/* -*- c-basic-offset: 2 -*- */
/*
  Copyright(C) 2015 Brazil

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License version 2.1 as published by the Free Software Foundation.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef GRN_EXPR_CODE_H
#define GRN_EXPR_CODE_H

#include "grn_db.h"

#ifdef __cplusplus
extern "C" {
#endif

unsigned int grn_expr_code_n_used_codes(grn_ctx *ctx,
                                        grn_expr_code *start,
                                        grn_expr_code *target);

#ifdef __cplusplus
}
#endif

#endif /* GRN_EXPR_CODE_H */

