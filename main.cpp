// main.cpp 主函数所在的空间
// 2013年1月21日19:33:17 By jiangcaiyang

#include <QCoreApplication>
#include <QBuffer>
#include <QtMultimedia>
#include <QtDebug>
#include "QOggVorbis.h"

class TestAudio
{
public:
    TestAudio( void )
    {
    }
    ~TestAudio( void )
    {
        Release( );
    }
    bool LoadOggFile( const QString& fileName )
    {
        if ( !m_OggVorbis.load( fileName ) ) return false;

        quint32 sampleRate = m_OggVorbis.sampleRate( );
        quint16 channels = m_OggVorbis.channels( );
        quint16 sampleSize = m_OggVorbis.bitsPerSample( );
        QStringList comments = m_OggVorbis.userComments( );
        QListIterator<QString> iterCmts( comments );

        qDebug( ) << "Ogg file information: " <<
                     "[sampleRate: " << sampleRate <<
                     "][channels: " << channels <<
                     "][sampleSize: " << sampleSize <<
                     ']';

        // 显示Ogg文件额外信息
        qDebug( ) << "Ogg comments: ";
        while ( iterCmts.hasNext( ) )
        {
            qDebug( ) << iterCmts.next( );
        }

        // 设置音频格式
        m_Format.setSampleRate( sampleRate );
        m_Format.setChannelCount( channels );
        m_Format.setSampleSize( sampleSize );
        m_Format.setCodec( "audio/pcm" );
        m_Format.setByteOrder( QAudioFormat::LittleEndian );
        m_Format.setSampleType( QAudioFormat::SignedInt );

        // 初始化音频设备
        m_DeviceInfo = QAudioDeviceInfo::defaultOutputDevice( );
        if ( !m_DeviceInfo.isFormatSupported( m_Format ) )
        {
            qDebug( ) << "Cannot support this format, try a corresponding format.\n";
            m_Format = m_DeviceInfo.nearestFormat( m_Format );
        }

        m_Buffer.setData( (const char*)m_OggVorbis.data( ), m_OggVorbis.dataSize( ) );
        m_pOutput = new QAudioOutput( m_DeviceInfo, m_Format, 0 );
        return true;
    }
    void Play( void )
    {
        m_Buffer.open( QIODevice::ReadOnly );
        m_pOutput->start( &m_Buffer );
    }
    void Release( void )
    {
        m_Buffer.close( );
        delete m_pOutput;
        m_pOutput = 0;
    }
private:
    QAudioFormat            m_Format;
    QAudioDeviceInfo        m_DeviceInfo;
    QOggVorbis              m_OggVorbis;
    QAudioOutput*           m_pOutput;
    QBuffer                 m_Buffer;
};



int main(int argc, char *argv[] )
{
    QCoreApplication a( argc, argv );

    // 读取并且播放
    TestAudio testAudio;
    if ( !testAudio.LoadOggFile( "../TestSound.ogg" ) ) return 1;
    qDebug( ) << "Read test sound successful!\n";
    testAudio.Play( );
    qDebug( ) << "Now Playing audio!\n";
    
    return a.exec();
}
