import React, { CSSProperties, useState } from "react";
import { ColorResult, SketchPicker } from "react-color";
import { Color } from "../protobuf/Color";
import "./Colorbox.css";

function LED({
   color,
   setColor,
   onChange,
}: {
   color: Color;
   setColor?: React.Dispatch<React.SetStateAction<Color>>;
   onChange?: (event: ColorResult) => void;
}) {
   const [showPicker, setShowPicker] = useState<boolean>(false);
   function componentToHex(c: number): string {
      var hex = c.toString(16);
      return hex.length === 1 ? "0" + hex : hex;
   }

   function rgbToHex(color: Color): string {
      return (
         "#" +
         componentToHex(color.r) +
         componentToHex(color.g) +
         componentToHex(color.b)
      );
   }
   const style: CSSProperties = {
      backgroundColor: rgbToHex(color),
   };
   const popover: CSSProperties = {
      position: "absolute",
      zIndex: 2,
   };
   const cover: CSSProperties = {
      position: "fixed",
      top: "0px",
      right: "0px",
      bottom: "0px",
      left: "0px",
   };

   const handleClick = () => {
      setColor && setShowPicker(!showPicker);
   };
   const handleClose = () => {
      setShowPicker(false);
   };
   const handleChange = (col: ColorResult) => {
      setColor && setColor(col.rgb);
      onChange && onChange(col);
   };
   return (
      <div>
         <div className="dot" style={style} onClick={handleClick} />
         {showPicker ? (
            <div style={popover}>
               <div style={cover} onClick={handleClose} />
               <SketchPicker color={color} onChange={handleChange} />
            </div>
         ) : null}
      </div>
   );
}

export default LED;
