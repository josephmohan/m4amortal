class M4amortal < Formula
  desc "Convert .m4a audio files to .wav from the command line"
  homepage "https://github.com/josephmohan/m4amortal"
  head "https://github.com/josephmohan/m4amortal.git", branch: "main"

  depends_on "ffmpeg"

  def install
    system "make"
    system "make", "install", "PREFIX=#{prefix}"
  end

  test do
    assert_match "Usage:", shell_output("#{bin}/m4amortal", 1)
  end
end
