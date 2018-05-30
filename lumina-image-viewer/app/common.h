#ifndef COMMON_H
#define COMMON_H

#include <QObject>
#include <QMap>
#include <Magick++.h>
/*
#
# Copyright (c) 2018, Ole-André Rodlie <ole.andre.rodlie@gmail.com> All rights reserved.
#
# Available under the 3-clause BSD license
# See the LICENSE file for full details
#
*/

class Common
{
public:
    static QMap<Magick::CompositeOperator, QString> compositeModes()
    {
        QMap<Magick::CompositeOperator, QString> result;

        result[MagickCore::OverCompositeOp] = QObject::tr("Over");
        result[MagickCore::OverlayCompositeOp] = QObject::tr("Overlay");
        result[MagickCore::ScreenCompositeOp] = QObject::tr("Screen");
        result[MagickCore::AtopCompositeOp] = QObject::tr("Atop");
        result[MagickCore::DissolveCompositeOp] = QObject::tr("Dissolve");
        result[MagickCore::DistortCompositeOp] = QObject::tr("Distort");
        result[MagickCore::MultiplyCompositeOp] = QObject::tr("Multiply");
        result[MagickCore::AddCompositeOp] = QObject::tr("Add");
        result[MagickCore::PlusCompositeOp] = QObject::tr("Plus");
        result[MagickCore::MinusCompositeOp] = QObject::tr("Minus");
        result[MagickCore::DivideCompositeOp] = QObject::tr("Divide");
        result[MagickCore::SubtractCompositeOp] = QObject::tr("Subtract");
        result[MagickCore::DifferenceCompositeOp] = QObject::tr("Difference");
        result[MagickCore::XorCompositeOp] = QObject::tr("Xor");
        result[MagickCore::BlendCompositeOp] = QObject::tr("Blend");
        result[MagickCore::ColorBurnCompositeOp] = QObject::tr("Color Burn");
        result[MagickCore::ColorDodgeCompositeOp] = QObject::tr("Color Dodge");
        result[MagickCore::HardLightCompositeOp] = QObject::tr("Hard Light");
        result[MagickCore::LightenCompositeOp] = QObject::tr("Lighten");
        result[MagickCore::LightenIntensityCompositeOp] = QObject::tr("Lighten Intensity");
        result[MagickCore::DarkenCompositeOp] = QObject::tr("Darken");
        result[MagickCore::DarkenIntensityCompositeOp] = QObject::tr("Darken Intensity");
        result[MagickCore::VividLightCompositeOp] = QObject::tr("Vivid Light");
        result[MagickCore::PinLightCompositeOp] = QObject::tr("Pin Light");
        result[MagickCore::SoftLightCompositeOp] = QObject::tr("Soft Light");
        result[MagickCore::PegtopLightCompositeOp] = QObject::tr("Pegtop Light");

        /*
        MagickCore::ModulusAddCompositeOp;
        MagickCore::HueCompositeOp;
        MagickCore::MinusDstCompositeOp;
        MagickCore::SaturateCompositeOp;
        MagickCore::MinusSrcCompositeOp;
        MagickCore::DivideSrcCompositeOp;
        MagickCore::MathematicsCompositeOp;
        MagickCore::LinearBurnCompositeOp;
        MagickCore::LinearDodgeCompositeOp;
        MagickCore::BlurCompositeOp;
        MagickCore::DivideDstCompositeOp;
        MagickCore::ThresholdCompositeOp;
        MagickCore::ModulusSubtractCompositeOp;
        MagickCore::SrcOverCompositeOp;
        MagickCore::SrcOutCompositeOp;
        MagickCore::SrcInCompositeOp;
        MagickCore::SrcCompositeOp;
        MagickCore::SrcAtopCompositeOp;
        MagickCore::ReplaceCompositeOp;
        MagickCore::OutCompositeOp;
        MagickCore::ModulateCompositeOp;
        MagickCore::LuminizeCompositeOp;
        MagickCore::LinearLightCompositeOp;
        MagickCore::InCompositeOp;
        MagickCore::HardMixCompositeOp;
        MagickCore::ExclusionCompositeOp;
        MagickCore::DisplaceCompositeOp;
        MagickCore::DstCompositeOp
        MagickCore::DstOverCompositeOp;
        MagickCore::DstOutCompositeOp;
        MagickCore::DstInCompositeOp;
        MagickCore::DstAtopCompositeOp;
        */

        return result;
    }
};

#endif // COMMON_H
