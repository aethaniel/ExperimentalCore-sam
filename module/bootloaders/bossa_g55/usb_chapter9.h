/*
  Copyright (c) 2016 Thibaut VIARD.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef _USB_CHAPTER9_H_
#define _USB_CHAPTER9_H_

/* USB standard request code */
#define STD_GET_STATUS_ZERO                                 (0x0080u)
#define STD_GET_STATUS_INTERFACE                            (0x0081u)
#define STD_GET_STATUS_ENDPOINT                             (0x0082u)

#define STD_CLEAR_FEATURE_ZERO                              (0x0100u)
#define STD_CLEAR_FEATURE_INTERFACE                         (0x0101u)
#define STD_CLEAR_FEATURE_ENDPOINT                          (0x0102u)

#define STD_SET_FEATURE_ZERO                                (0x0300u)
#define STD_SET_FEATURE_INTERFACE                           (0x0301u)
#define STD_SET_FEATURE_ENDPOINT                            (0x0302u)

#define STD_SET_ADDRESS                                     (0x0500u)
#define STD_GET_DESCRIPTOR                                  (0x0680u)
#define STD_SET_DESCRIPTOR                                  (0x0700u)
#define STD_GET_CONFIGURATION                               (0x0880u)
#define STD_SET_CONFIGURATION                               (0x0900u)
#define STD_GET_INTERFACE                                   (0x0A81u)
#define STD_SET_INTERFACE                                   (0x0B01u)
#define STD_SYNCH_FRAME                                     (0x0C82u)

#define STD_GET_DESCRIPTOR_DEVICE                           (1u)
#define STD_GET_DESCRIPTOR_CONFIGURATION                    (2u)
#define STD_GET_DESCRIPTOR_STRING                           (3u)
#define STD_GET_DESCRIPTOR_INTERFACE                        (4u)
#define STD_GET_DESCRIPTOR_ENDPOINT                         (5u)
#define STD_GET_DESCRIPTOR_DEVICE_QUALIFIER                 (6u)
#define STD_GET_DESCRIPTOR_OTHER_SPEED_CONFIGURATION        (7u)
#define STD_GET_DESCRIPTOR_INTERFACE_POWER1                 (8u)

#define FEATURE_ENDPOINT_HALT                               (0u)
#define FEATURE_DEVICE_REMOTE_WAKEUP                        (1u)
#define FEATURE_TEST_MODE                                   (2u)

#if 0 // TODO: pending validation
#define STRING_INDEX_LANGUAGES                              (0x00u)
#define STRING_INDEX_MANUFACTURER                           (0x01u)
#define STRING_INDEX_PRODUCT                                (0x02u)
#endif // 0

#endif // _USB_CHAPTER9_H_
