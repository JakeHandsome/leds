/* eslint-disable */
import Long from "long";
import _m0 from "protobufjs/minimal";

export const protobufPackage = "";

export interface Color {
  r: number;
  g: number;
  b: number;
}

const baseColor: object = { r: 0, g: 0, b: 0 };

export const Color = {
  encode(message: Color, writer: _m0.Writer = _m0.Writer.create()): _m0.Writer {
    if (message.r !== 0) {
      writer.uint32(8).int32(message.r);
    }
    if (message.g !== 0) {
      writer.uint32(16).int32(message.g);
    }
    if (message.b !== 0) {
      writer.uint32(24).int32(message.b);
    }
    return writer;
  },

  decode(input: _m0.Reader | Uint8Array, length?: number): Color {
    const reader = input instanceof _m0.Reader ? input : new _m0.Reader(input);
    let end = length === undefined ? reader.len : reader.pos + length;
    const message = { ...baseColor } as Color;
    while (reader.pos < end) {
      const tag = reader.uint32();
      switch (tag >>> 3) {
        case 1:
          message.r = reader.int32();
          break;
        case 2:
          message.g = reader.int32();
          break;
        case 3:
          message.b = reader.int32();
          break;
        default:
          reader.skipType(tag & 7);
          break;
      }
    }
    return message;
  },

  fromJSON(object: any): Color {
    const message = { ...baseColor } as Color;
    if (object.r !== undefined && object.r !== null) {
      message.r = Number(object.r);
    } else {
      message.r = 0;
    }
    if (object.g !== undefined && object.g !== null) {
      message.g = Number(object.g);
    } else {
      message.g = 0;
    }
    if (object.b !== undefined && object.b !== null) {
      message.b = Number(object.b);
    } else {
      message.b = 0;
    }
    return message;
  },

  toJSON(message: Color): unknown {
    const obj: any = {};
    message.r !== undefined && (obj.r = message.r);
    message.g !== undefined && (obj.g = message.g);
    message.b !== undefined && (obj.b = message.b);
    return obj;
  },

  fromPartial(object: DeepPartial<Color>): Color {
    const message = { ...baseColor } as Color;
    if (object.r !== undefined && object.r !== null) {
      message.r = object.r;
    } else {
      message.r = 0;
    }
    if (object.g !== undefined && object.g !== null) {
      message.g = object.g;
    } else {
      message.g = 0;
    }
    if (object.b !== undefined && object.b !== null) {
      message.b = object.b;
    } else {
      message.b = 0;
    }
    return message;
  },
};

type Builtin =
  | Date
  | Function
  | Uint8Array
  | string
  | number
  | boolean
  | undefined;
export type DeepPartial<T> = T extends Builtin
  ? T
  : T extends Array<infer U>
  ? Array<DeepPartial<U>>
  : T extends ReadonlyArray<infer U>
  ? ReadonlyArray<DeepPartial<U>>
  : T extends {}
  ? { [K in keyof T]?: DeepPartial<T[K]> }
  : Partial<T>;

if (_m0.util.Long !== Long) {
  _m0.util.Long = Long as any;
  _m0.configure();
}
