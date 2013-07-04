#ifndef AUDIOCDTEST_H
#define AUDIOCDTEST_H

#include <QDebug>
#include <QObject>
#include <QString>

#include <solid/block.h>
#include <solid/deviceinterface.h>
#include <solid/devicenotifier.h>
#include <solid/device.h>
#include <solid/opticaldisc.h>
#include <solid/opticaldrive.h>

class AudioCdTest: public QObject
{
   Q_OBJECT

    public:
        void init()
        {    
            connect( Solid::DeviceNotifier::instance(), SIGNAL(deviceAdded(QString)),
                     SLOT(slotAddSolidDevice(const QString&)) );
            connect( Solid::DeviceNotifier::instance(), SIGNAL(deviceRemoved(QString)),
                     SLOT(slotRemoveSolidDevice(const QString&)) );

            // detect AudioCd devices that were already connected on startup
            QList<Solid::Device> devices = Solid::Device::listFromType( Solid::DeviceInterface::OpticalDisc );
            foreach( const Solid::Device &device, devices )
            {
                qDebug() << device.udi();
                if( identifySolidDevice( device.udi() ) )
                    qDebug() << "Device with udi" << device.udi() << "is audiocd";
            }
        }
        ~AudioCdTest() {}

    private slots:
        /**
         * Called when solid notifier detects a new device has been added
         */
        void slotAddSolidDevice( const QString &udi )
        {
            if( identifySolidDevice( udi ) )
                qDebug() << "New device with udi" << udi << "is audiocd";
        }
        /**
         * Called when solid notifier detects a device has been removed
         */
        void slotRemoveSolidDevice( const QString &udi )
        {
            if( identifySolidDevice( udi ) )
                qDebug() << "AudioCD with udi" << udi << "was ejected";
        }
        private:
        /**
         * Checks whether a solid device is a CD
         */
        bool identifySolidDevice( const QString &udi ) const
        {
            Solid::Device device( udi );
            if( device.is<Solid::OpticalDisc>() )
            {
                const Solid::OpticalDisc * opt = device.as<Solid::OpticalDisc>();
                if ( opt->availableContent() & Solid::OpticalDisc::Audio )
                    return true;
            }
            return false;
        }
};
#endif
