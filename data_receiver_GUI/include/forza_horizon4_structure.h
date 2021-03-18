#pragma once
#include<string>
#include<fmt/format.h>

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
    inline constexpr int32_t convertIsRaceOn() const {
        return IsRaceOn;
    }
    inline constexpr uint32_t convertTimestampMS() const {
        return TimestampMS;
    }
    inline constexpr float convertEngineMaxRpm() const {
        return EngineMaxRpm;
    }
    inline constexpr float convertEngineIdleRpm() const {
        return EngineIdleRpm;
    }
    inline constexpr float convertCurrentEngineRpm() const {
        return CurrentEngineRpm;
    }
    inline constexpr float convertAccelerationX() const {
        return AccelerationX;
    }
    inline constexpr float convertAccelerationY() const {
        return AccelerationY;
    }
    inline constexpr float convertAccelerationZ() const {
        return AccelerationZ;
    }
    inline constexpr float convertVelocityX() const {
        return VelocityX;
    }
    inline constexpr float convertVelocityY() const {
        return VelocityY;
    }
    inline constexpr float convertVelocityZ() const {
        return VelocityZ;
    }
    inline constexpr float convertAngularVelocityX() const {
        return AngularVelocityX;
    }
    inline constexpr float convertAngularVelocityY() const {
        return AngularVelocityY;
    }
    inline constexpr float convertAngularVelocityZ() const {
        return AngularVelocityZ;
    }
    inline constexpr float convertYaw() const {
        return Yaw;
    }
    inline constexpr float convertPitch() const {
        return Pitch;
    }
    inline constexpr float convertRoll() const {
        return Roll;
    }
    inline constexpr float convertNormalizedSuspensionTravelFrontLeft() const {
        return NormalizedSuspensionTravelFrontLeft;
    }
    inline constexpr float convertNormalizedSuspensionTravelFrontRight() const {
        return NormalizedSuspensionTravelFrontRight;
    }
    inline constexpr float convertNormalizedSuspensionTravelRearLeft() const {
        return NormalizedSuspensionTravelRearLeft;
    }
    inline constexpr float convertNormalizedSuspensionTravelRearRight() const {
        return NormalizedSuspensionTravelRearRight;
    }
    inline constexpr float convertTireSlipRatioFrontLeft() const {
        return TireSlipRatioFrontLeft;
    }
    inline constexpr float convertTireSlipRatioFrontRight() const {
        return TireSlipRatioFrontRight;
    }
    inline constexpr float convertTireSlipRatioRearLeft() const {
        return TireSlipRatioRearLeft;
    }
    inline constexpr float convertTireSlipRatioRearRight() const {
        return TireSlipRatioRearRight;
    }
    inline constexpr float convertWheelRotationSpeedFrontLeft() const {
        return WheelRotationSpeedFrontLeft;
    }
    inline constexpr float convertWheelRotationSpeedFrontRight() const {
        return WheelRotationSpeedFrontRight;
    }
    inline constexpr float convertWheelRotationSpeedRearLeft() const {
        return WheelRotationSpeedRearLeft;
    }
    inline constexpr float convertWheelRotationSpeedRearRight() const {
        return WheelRotationSpeedRearRight;
    }
    inline constexpr int32_t convertWheelOnRumbleStripFrontLeft() const {
        return WheelOnRumbleStripFrontLeft;
    }
    inline constexpr int32_t convertWheelOnRumbleStripFrontRight() const {
        return WheelOnRumbleStripFrontRight;
    }
    inline constexpr int32_t convertWheelOnRumbleStripRearLeft() const {
        return WheelOnRumbleStripRearLeft;
    }
    inline constexpr int32_t convertWheelOnRumbleStripRearRight() const {
        return WheelOnRumbleStripRearRight;
    }
    inline constexpr float convertWheelInPuddleDepthFrontLeft() const {
        return WheelInPuddleDepthFrontLeft;
    }
    inline constexpr float convertWheelInPuddleDepthFrontRight() const {
        return WheelInPuddleDepthFrontRight;
    }
    inline constexpr float convertWheelInPuddleDepthRearLeft() const {
        return WheelInPuddleDepthRearLeft;
    }
    inline constexpr float convertWheelInPuddleDepthRearRight() const {
        return WheelInPuddleDepthRearRight;
    }
    inline constexpr float convertSurfaceRumbleFrontLeft() const {
        return SurfaceRumbleFrontLeft;
    }
    inline constexpr float convertSurfaceRumbleFrontRight() const {
        return SurfaceRumbleFrontRight;
    }
    inline constexpr float convertSurfaceRumbleRearLeft() const {
        return SurfaceRumbleRearLeft;
    }
    inline constexpr float convertSurfaceRumbleRearRight() const {
        return SurfaceRumbleRearRight;
    }
    inline constexpr float convertTireSlipAngleFrontLeft() const {
        return TireSlipAngleFrontLeft;
    }
    inline constexpr float convertTireSlipAngleFrontRight() const {
        return TireSlipAngleFrontRight;
    }
    inline constexpr float convertTireSlipAngleRearLeft() const {
        return TireSlipAngleRearLeft;
    }
    inline constexpr float convertTireSlipAngleRearRight() const {
        return TireSlipAngleRearRight;
    }
    inline constexpr float convertTireCombinedSlipFrontLeft() const {
        return TireCombinedSlipFrontLeft;
    }
    inline constexpr float convertTireCombinedSlipFrontRight() const {
        return TireCombinedSlipFrontRight;
    }
    inline constexpr float convertTireCombinedSlipRearLeft() const {
        return TireCombinedSlipRearLeft;
    }
    inline constexpr float convertTireCombinedSlipRearRight() const {
        return TireCombinedSlipRearRight;
    }
    inline constexpr float convertSuspensionTravelMetersFrontLeft() const {
        return SuspensionTravelMetersFrontLeft;
    }
    inline constexpr float convertSuspensionTravelMetersFrontRight() const {
        return SuspensionTravelMetersFrontRight;
    }
    inline constexpr float convertSuspensionTravelMetersRearLeft() const {
        return SuspensionTravelMetersRearLeft;
    }
    inline constexpr float convertSuspensionTravelMetersRearRight() const {
        return SuspensionTravelMetersRearRight;
    }
    inline constexpr int32_t convertCarOrdinal() const {
        return CarOrdinal;
    }
    inline constexpr int32_t convertCarClass() const {
        return CarClass;
    }
    inline constexpr int32_t convertCarPerformanceIndex() const {
        return CarPerformanceIndex;
    }
    inline constexpr int32_t convertDrivetrainType() const {
        return DrivetrainType;
    }
    inline constexpr int32_t convertNumCylinders() const {
        return NumCylinders;
    }
    inline constexpr float convertPositionX() const {
        return PositionX;
    }
    inline constexpr float convertPositionY() const {
        return PositionY;
    }
    inline constexpr float convertPositionZ() const {
        return PositionZ;
    }
    inline constexpr float convertSpeed() const {
        return 2.237f * Speed;
    }
    inline constexpr float convertPower() const {
        return 0.0013410218586563f * Power;
    }
    inline constexpr float convertTorque() const {
        return Torque;
    }
    inline constexpr float convertTireTempFrontLeft() const {
        return TireTempFrontLeft;
    }
    inline constexpr float convertTireTempFrontRight() const {
        return TireTempFrontRight;
    }
    inline constexpr float convertTireTempRearLeft() const {
        return TireTempRearLeft;
    }
    inline constexpr float convertTireTempRearRight() const {
        return TireTempRearRight;
    }
    inline constexpr float convertBoost() const {
        return Boost;
    }
    inline constexpr float convertFuel() const {
        return Fuel;
    }
    inline constexpr float convertDistanceTraveled() const {
        return DistanceTraveled;
    }
    inline constexpr float convertBestLap() const {
        return BestLap;
    }
    inline constexpr float convertLastLap() const {
        return LastLap;
    }
    inline constexpr float convertCurrentLap() const {
        return CurrentLap;
    }
    inline constexpr float convertCurrentRaceTime() const {
        return CurrentRaceTime;
    }
    inline constexpr uint16_t convertLapNumber() const {
        return LapNumber;
    }
    inline constexpr uint8_t convertRacePosition() const {
        return RacePosition;
    }
    inline constexpr uint8_t convertAccel() const {
        return Accel;
    }
    inline constexpr uint8_t convertBrake() const {
        return Brake;
    }
    inline constexpr uint8_t convertClutch() const {
        return Clutch;
    }
    inline constexpr uint8_t convertHandBrake() const {
        return HandBrake;
    }
    inline constexpr uint8_t convertGear() const {
        return Gear;
    }
    inline constexpr int8_t convertSteer() const {
        return Steer;
    }
    inline constexpr int8_t convertNormalizedDrivingLine() const {
        return NormalizedDrivingLine;
    }
    inline constexpr int8_t convertNormalizedAIBrakeDifference() const {
        return NormalizedAIBrakeDifference;
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
        return format_to(ctx.out(), "{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}", data.convertIsRaceOn(),
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
            data.convertNormalizedAIBrakeDifference());
    }
};

std::string printCSVHeader()
{
    return "IsRaceOn, TimestampMS, EngineMaxRpm, EngineIdleRpm, CurrentEngineRpm, AccelerationX, AccelerationY, AccelerationZ, VelocityX, VelocityY, VelocityZ, AngularVelocityX, AngularVelocityY, AngularVelocityZ, Yaw, Pitch, Roll, NormalizedSuspensionTravelFrontLeft, NormalizedSuspensionTravelFrontRight, NormalizedSuspensionTravelRearLeft, NormalizedSuspensionTravelRearRight, TireSlipRatioFrontLeft, TireSlipRatioFrontRight, TireSlipRatioRearLeft, TireSlipRatioRearRight, WheelRotationSpeedFrontLeft, WheelRotationSpeedFrontRight, WheelRotationSpeedRearLeft, WheelRotationSpeedRearRight, WheelOnRumbleStripFrontLeft, WheelOnRumbleStripFrontRight, WheelOnRumbleStripRearLeft, WheelOnRumbleStripRearRight, WheelInPuddleDepthFrontLeft, WheelInPuddleDepthFrontRight, WheelInPuddleDepthRearLeft, WheelInPuddleDepthRearRight, SurfaceRumbleFrontLeft, SurfaceRumbleFrontRight, SurfaceRumbleRearLeft, SurfaceRumbleRearRight, TireSlipAngleFrontLeft, TireSlipAngleFrontRight, TireSlipAngleRearLeft, TireSlipAngleRearRight, TireCombinedSlipFrontLeft, TireCombinedSlipFrontRight, TireCombinedSlipRearLeft, TireCombinedSlipRearRight, SuspensionTravelMetersFrontLeft, SuspensionTravelMetersFrontRight, SuspensionTravelMetersRearLeft, SuspensionTravelMetersRearRight, CarOrdinal, CarClass, CarPerformanceIndex, DrivetrainType, NumCylinders, PositionX, PositionY, PositionZ, Speed, Power, Torque, TireTempFrontLeft, TireTempFrontRight, TireTempRearLeft, TireTempRearRight, Boost, Fuel, DistanceTraveled, BestLap, LastLap, CurrentLap, CurrentRaceTime, LapNumber, RacePosition, Accel, Brake, Clutch, HandBrake, Gear, Steer, NormalizedDrivingLine, NormalizedAIBrakeDifference";
}