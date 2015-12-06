using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace OpenCV_Video
{
    public enum VideoProperty
    {
        PositionMillisecond = 0,
        PositionFrames = 1,
        PositionAviRatio = 2,
        FrameWidth = 3,
        FrameHeight = 4,
        Fps = 5,
        FourCc = 6,
        FrameCount = 7,
        Format = 8,
        Mode = 9,
        Brightness = 10,
        Contrast = 11,
        Saturation = 12,
        Hue = 13,
        Gain = 14,
        Exposure = 15,
        ConvertRgb = 16,
        WhiteBalanceU = 17,
        WhiteBalanceV = 26,
        Rectification = 18,
        IsoSpeed = 30,
        BufferSize = 38
    }

    public class VideoCapture
    {
        /// <summary>
        /// DLL Location.
        /// </summary>
        private const string DllLocation = "VideoWrapper.dll";

#region Related Dll Import

        [DllImport(DllLocation, EntryPoint = "_VideoCapture_Get@8")]
        private static extern double VideoCapure_Get(int handle, int propId);

        [DllImport(DllLocation, EntryPoint = "_VideoCapture_Grab@4")]
        private static extern bool VideoCapture_Grab(int handle);

        [DllImport(DllLocation, EntryPoint = "_VideoCapture_IsOpened@4")]
        private static extern bool VideoCapture_IsOpened(int handle);

        [DllImport(DllLocation, EntryPoint = "_VideoCapture_Open@4")]
        private static extern int VideoCapture_Open([MarshalAs(UnmanagedType.LPStr)] string filename);

        [DllImport(DllLocation, EntryPoint = "_VideoCapture_Release@4")]
        private static extern void VideoCapture_Release(int handle);

        [DllImport(DllLocation, EntryPoint = "_VideoCapture_Read@20")]
        private static extern bool VideoCapture_Read(int handle, [MarshalAs(UnmanagedType.LPArray)] byte[] frameData,
            ref int frameLength, int expectedWidth, int expectedHeight);

 
#endregion
    }
}
