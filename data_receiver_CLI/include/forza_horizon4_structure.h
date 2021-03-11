#pragma once
#include"telemetry_type.h"
#include<string>
#include<fmt/format.h>

__declspec(align(1))
class ForzaHorizon4Data
{
public:
    int32_t IsRaceOn;
    uint32_t TimestampMS;
    float EngineMaxRpm;
    float EngineIdleRpm;
    float CurrentEngineRpm;
    float AccelerationX;
    float AccelerationY;
    float AccelerationZ;
    float VelocityX;
    float VelocityY;
    float VelocityZ;
    float AngularVelocityX;
    float AngularVelocityY;
    float AngularVelocityZ;
    float Yaw;
    float Pitch;
    float Roll;
    float NormalizedSuspensionTravelFrontLeft;
    float NormalizedSuspensionTravelFrontRight;
    float NormalizedSuspensionTravelRearLeft;
    float NormalizedSuspensionTravelRearRight;
    float TireSlipRatioFrontLeft;
    float TireSlipRatioFrontRight;
    float TireSlipRatioRearLeft;
    float TireSlipRatioRearRight;
    float WheelRotationSpeedFrontLeft;
    float WheelRotationSpeedFrontRight;
    float WheelRotationSpeedRearLeft;
    float WheelRotationSpeedRearRight;
    int32_t WheelOnRumbleStripFrontLeft;
    int32_t WheelOnRumbleStripFrontRight;
    int32_t WheelOnRumbleStripRearLeft;
    int32_t WheelOnRumbleStripRearRight;
    float WheelInPuddleDepthFrontLeft;
    float WheelInPuddleDepthFrontRight;
    float WheelInPuddleDepthRearLeft;
    float WheelInPuddleDepthRearRight;
    float SurfaceRumbleFrontLeft;
    float SurfaceRumbleFrontRight;
    float SurfaceRumbleRearLeft;
    float SurfaceRumbleRearRight;
    float TireSlipAngleFrontLeft;
    float TireSlipAngleFrontRight;
    float TireSlipAngleRearLeft;
    float TireSlipAngleRearRight;
    float TireCombinedSlipFrontLeft;
    float TireCombinedSlipFrontRight;
    float TireCombinedSlipRearLeft;
    float TireCombinedSlipRearRight;
    float SuspensionTravelMetersFrontLeft;
    float SuspensionTravelMetersFrontRight;
    float SuspensionTravelMetersRearLeft;
    float SuspensionTravelMetersRearRight;
    int32_t CarOrdinal;
    int32_t CarClass;
    int32_t CarPerformanceIndex;
    int32_t DrivetrainType;
    int32_t NumCylinders;
    int8_t HorizonPlaceholder[12];
    float PositionX;
    float PositionY;
    float PositionZ;
    float Speed;
    float Power;
    float Torque;
    float TireTempFrontLeft;
    float TireTempFrontRight;
    float TireTempRearLeft;
    float TireTempRearRight;
    float Boost;
    float Fuel;
    float DistanceTraveled;
    float BestLap;
    float LastLap;
    float CurrentLap;
    float CurrentRaceTime;
    uint16_t LapNumber;
    uint8_t RacePosition;
    uint8_t Accel;
    uint8_t Brake;
    uint8_t Clutch;
    uint8_t HandBrake;
    uint8_t Gear;
    int8_t Steer;
    int8_t NormalizedDrivingLine;
    int8_t NormalizedAIBrakeDifference;
    int32_t convertIsRaceOn() {
        return 1.0000000000000000f * IsRaceOn;
    }
    uint32_t convertTimestampMS() {
        return 1.0000000000000000f * TimestampMS;
    }
    float convertEngineMaxRpm() {
        return 1.0000000000000000f * EngineMaxRpm;
    }
    float convertEngineIdleRpm() {
        return 1.0000000000000000f * EngineIdleRpm;
    }
    float convertCurrentEngineRpm() {
        return 1.0000000000000000f * CurrentEngineRpm;
    }
    float convertAccelerationX() {
        return 1.0000000000000000f * AccelerationX;
    }
    float convertAccelerationY() {
        return 1.0000000000000000f * AccelerationY;
    }
    float convertAccelerationZ() {
        return 1.0000000000000000f * AccelerationZ;
    }
    float convertVelocityX() {
        return 1.0000000000000000f * VelocityX;
    }
    float convertVelocityY() {
        return 1.0000000000000000f * VelocityY;
    }
    float convertVelocityZ() {
        return 1.0000000000000000f * VelocityZ;
    }
    float convertAngularVelocityX() {
        return 1.0000000000000000f * AngularVelocityX;
    }
    float convertAngularVelocityY() {
        return 1.0000000000000000f * AngularVelocityY;
    }
    float convertAngularVelocityZ() {
        return 1.0000000000000000f * AngularVelocityZ;
    }
    float convertYaw() {
        return 1.0000000000000000f * Yaw;
    }
    float convertPitch() {
        return 1.0000000000000000f * Pitch;
    }
    float convertRoll() {
        return 1.0000000000000000f * Roll;
    }
    float convertNormalizedSuspensionTravelFrontLeft() {
        return 1.0000000000000000f * NormalizedSuspensionTravelFrontLeft;
    }
    float convertNormalizedSuspensionTravelFrontRight() {
        return 1.0000000000000000f * NormalizedSuspensionTravelFrontRight;
    }
    float convertNormalizedSuspensionTravelRearLeft() {
        return 1.0000000000000000f * NormalizedSuspensionTravelRearLeft;
    }
    float convertNormalizedSuspensionTravelRearRight() {
        return 1.0000000000000000f * NormalizedSuspensionTravelRearRight;
    }
    float convertTireSlipRatioFrontLeft() {
        return 1.0000000000000000f * TireSlipRatioFrontLeft;
    }
    float convertTireSlipRatioFrontRight() {
        return 1.0000000000000000f * TireSlipRatioFrontRight;
    }
    float convertTireSlipRatioRearLeft() {
        return 1.0000000000000000f * TireSlipRatioRearLeft;
    }
    float convertTireSlipRatioRearRight() {
        return 1.0000000000000000f * TireSlipRatioRearRight;
    }
    float convertWheelRotationSpeedFrontLeft() {
        return 1.0000000000000000f * WheelRotationSpeedFrontLeft;
    }
    float convertWheelRotationSpeedFrontRight() {
        return 1.0000000000000000f * WheelRotationSpeedFrontRight;
    }
    float convertWheelRotationSpeedRearLeft() {
        return 1.0000000000000000f * WheelRotationSpeedRearLeft;
    }
    float convertWheelRotationSpeedRearRight() {
        return 1.0000000000000000f * WheelRotationSpeedRearRight;
    }
    int32_t convertWheelOnRumbleStripFrontLeft() {
        return 1.0000000000000000f * WheelOnRumbleStripFrontLeft;
    }
    int32_t convertWheelOnRumbleStripFrontRight() {
        return 1.0000000000000000f * WheelOnRumbleStripFrontRight;
    }
    int32_t convertWheelOnRumbleStripRearLeft() {
        return 1.0000000000000000f * WheelOnRumbleStripRearLeft;
    }
    int32_t convertWheelOnRumbleStripRearRight() {
        return 1.0000000000000000f * WheelOnRumbleStripRearRight;
    }
    float convertWheelInPuddleDepthFrontLeft() {
        return 1.0000000000000000f * WheelInPuddleDepthFrontLeft;
    }
    float convertWheelInPuddleDepthFrontRight() {
        return 1.0000000000000000f * WheelInPuddleDepthFrontRight;
    }
    float convertWheelInPuddleDepthRearLeft() {
        return 1.0000000000000000f * WheelInPuddleDepthRearLeft;
    }
    float convertWheelInPuddleDepthRearRight() {
        return 1.0000000000000000f * WheelInPuddleDepthRearRight;
    }
    float convertSurfaceRumbleFrontLeft() {
        return 1.0000000000000000f * SurfaceRumbleFrontLeft;
    }
    float convertSurfaceRumbleFrontRight() {
        return 1.0000000000000000f * SurfaceRumbleFrontRight;
    }
    float convertSurfaceRumbleRearLeft() {
        return 1.0000000000000000f * SurfaceRumbleRearLeft;
    }
    float convertSurfaceRumbleRearRight() {
        return 1.0000000000000000f * SurfaceRumbleRearRight;
    }
    float convertTireSlipAngleFrontLeft() {
        return 1.0000000000000000f * TireSlipAngleFrontLeft;
    }
    float convertTireSlipAngleFrontRight() {
        return 1.0000000000000000f * TireSlipAngleFrontRight;
    }
    float convertTireSlipAngleRearLeft() {
        return 1.0000000000000000f * TireSlipAngleRearLeft;
    }
    float convertTireSlipAngleRearRight() {
        return 1.0000000000000000f * TireSlipAngleRearRight;
    }
    float convertTireCombinedSlipFrontLeft() {
        return 1.0000000000000000f * TireCombinedSlipFrontLeft;
    }
    float convertTireCombinedSlipFrontRight() {
        return 1.0000000000000000f * TireCombinedSlipFrontRight;
    }
    float convertTireCombinedSlipRearLeft() {
        return 1.0000000000000000f * TireCombinedSlipRearLeft;
    }
    float convertTireCombinedSlipRearRight() {
        return 1.0000000000000000f * TireCombinedSlipRearRight;
    }
    float convertSuspensionTravelMetersFrontLeft() {
        return 1.0000000000000000f * SuspensionTravelMetersFrontLeft;
    }
    float convertSuspensionTravelMetersFrontRight() {
        return 1.0000000000000000f * SuspensionTravelMetersFrontRight;
    }
    float convertSuspensionTravelMetersRearLeft() {
        return 1.0000000000000000f * SuspensionTravelMetersRearLeft;
    }
    float convertSuspensionTravelMetersRearRight() {
        return 1.0000000000000000f * SuspensionTravelMetersRearRight;
    }
    int32_t convertCarOrdinal() {
        return 1.0000000000000000f * CarOrdinal;
    }
    int32_t convertCarClass() {
        return 1.0000000000000000f * CarClass;
    }
    int32_t convertCarPerformanceIndex() {
        return 1.0000000000000000f * CarPerformanceIndex;
    }
    int32_t convertDrivetrainType() {
        return 1.0000000000000000f * DrivetrainType;
    }
    int32_t convertNumCylinders() {
        return 1.0000000000000000f * NumCylinders;
    }
    float convertPositionX() {
        return 1.0000000000000000f * PositionX;
    }
    float convertPositionY() {
        return 1.0000000000000000f * PositionY;
    }
    float convertPositionZ() {
        return 1.0000000000000000f * PositionZ;
    }
    float convertSpeed() {
        return 2.2369999885559082f * Speed;
    }
    float convertPower() {
        return 0.0013410218525678f * Power;
    }
    float convertTorque() {
        return 1.0000000000000000f * Torque;
    }
    float convertTireTempFrontLeft() {
        return 1.0000000000000000f * TireTempFrontLeft;
    }
    float convertTireTempFrontRight() {
        return 1.0000000000000000f * TireTempFrontRight;
    }
    float convertTireTempRearLeft() {
        return 1.0000000000000000f * TireTempRearLeft;
    }
    float convertTireTempRearRight() {
        return 1.0000000000000000f * TireTempRearRight;
    }
    float convertBoost() {
        return 1.0000000000000000f * Boost;
    }
    float convertFuel() {
        return 1.0000000000000000f * Fuel;
    }
    float convertDistanceTraveled() {
        return 1.0000000000000000f * DistanceTraveled;
    }
    float convertBestLap() {
        return 1.0000000000000000f * BestLap;
    }
    float convertLastLap() {
        return 1.0000000000000000f * LastLap;
    }
    float convertCurrentLap() {
        return 1.0000000000000000f * CurrentLap;
    }
    float convertCurrentRaceTime() {
        return 1.0000000000000000f * CurrentRaceTime;
    }
    uint16_t convertLapNumber() {
        return 1.0000000000000000f * LapNumber;
    }
    uint8_t convertRacePosition() {
        return 1.0000000000000000f * RacePosition;
    }
    uint8_t convertAccel() {
        return 1.0000000000000000f * Accel;
    }
    uint8_t convertBrake() {
        return 1.0000000000000000f * Brake;
    }
    uint8_t convertClutch() {
        return 1.0000000000000000f * Clutch;
    }
    uint8_t convertHandBrake() {
        return 1.0000000000000000f * HandBrake;
    }
    uint8_t convertGear() {
        return 1.0000000000000000f * Gear;
    }
    int8_t convertSteer() {
        return 1.0000000000000000f * Steer;
    }
    int8_t convertNormalizedDrivingLine() {
        return 1.0000000000000000f * NormalizedDrivingLine;
    }
    int8_t convertNormalizedAIBrakeDifference() {
        return 1.0000000000000000f * NormalizedAIBrakeDifference;
    }

};

template<>
struct fmt::formatter<ForzaHorizon4Data>
{
    constexpr auto parse(format_parse_context& ctx)
    {
        auto begin = ctx.begin();
        auto end = ctx.end();

        if (begin != end && *begin != '}')
            throw format_error("invalid format");
        return begin;
    }

    template<typename FormatContext>
    auto format(const ForzaHorizon4Data& data, FormatContext& ctx)
    {
        return format_to(ctx.out(), "{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, ", data.convertIsRaceOn(),
            data.convertTimestampMS(),
            data.convertEngineMaxRpm(),
            data.convertEngineIdleRpm(),
            data.convertCurrentEngineRpm(),
            data.convertAccelerationX(),
            data.convertAccelerationY(),
            data.convertAccelerationZ(),
            data.convertVelocityX(),
            data.convertVelocityY(),
            data.convertVelocityZ(),
            data.convertAngularVelocityX(),
            data.convertAngularVelocityY(),
            data.convertAngularVelocityZ(),
            data.convertYaw(),
            data.convertPitch(),
            data.convertRoll(),
            data.convertNormalizedSuspensionTravelFrontLeft(),
            data.convertNormalizedSuspensionTravelFrontRight(),
            data.convertNormalizedSuspensionTravelRearLeft(),
            data.convertNormalizedSuspensionTravelRearRight(),
            data.convertTireSlipRatioFrontLeft(),
            data.convertTireSlipRatioFrontRight(),
            data.convertTireSlipRatioRearLeft(),
            data.convertTireSlipRatioRearRight(),
            data.convertWheelRotationSpeedFrontLeft(),
            data.convertWheelRotationSpeedFrontRight(),
            data.convertWheelRotationSpeedRearLeft(),
            data.convertWheelRotationSpeedRearRight(),
            data.convertWheelOnRumbleStripFrontLeft(),
            data.convertWheelOnRumbleStripFrontRight(),
            data.convertWheelOnRumbleStripRearLeft(),
            data.convertWheelOnRumbleStripRearRight(),
            data.convertWheelInPuddleDepthFrontLeft(),
            data.convertWheelInPuddleDepthFrontRight(),
            data.convertWheelInPuddleDepthRearLeft(),
            data.convertWheelInPuddleDepthRearRight(),
            data.convertSurfaceRumbleFrontLeft(),
            data.convertSurfaceRumbleFrontRight(),
            data.convertSurfaceRumbleRearLeft(),
            data.convertSurfaceRumbleRearRight(),
            data.convertTireSlipAngleFrontLeft(),
            data.convertTireSlipAngleFrontRight(),
            data.convertTireSlipAngleRearLeft(),
            data.convertTireSlipAngleRearRight(),
            data.convertTireCombinedSlipFrontLeft(),
            data.convertTireCombinedSlipFrontRight(),
            data.convertTireCombinedSlipRearLeft(),
            data.convertTireCombinedSlipRearRight(),
            data.convertSuspensionTravelMetersFrontLeft(),
            data.convertSuspensionTravelMetersFrontRight(),
            data.convertSuspensionTravelMetersRearLeft(),
            data.convertSuspensionTravelMetersRearRight(),
            data.convertCarOrdinal(),
            data.convertCarClass(),
            data.convertCarPerformanceIndex(),
            data.convertDrivetrainType(),
            data.convertNumCylinders(),
            data.convertHorizonPlaceholder(),
            data.convertPositionX(),
            data.convertPositionY(),
            data.convertPositionZ(),
            data.convertSpeed(),
            data.convertPower(),
            data.convertTorque(),
            data.convertTireTempFrontLeft(),
            data.convertTireTempFrontRight(),
            data.convertTireTempRearLeft(),
            data.convertTireTempRearRight(),
            data.convertBoost(),
            data.convertFuel(),
            data.convertDistanceTraveled(),
            data.convertBestLap(),
            data.convertLastLap(),
            data.convertCurrentLap(),
            data.convertCurrentRaceTime(),
            data.convertLapNumber(),
            data.convertRacePosition(),
            data.convertAccel(),
            data.convertBrake(),
            data.convertClutch(),
            data.convertHandBrake(),
            data.convertGear(),
            data.convertSteer(),
            data.convertNormalizedDrivingLine(),
            data.convertNormalizedAIBrakeDifference(),
            );
    }
};